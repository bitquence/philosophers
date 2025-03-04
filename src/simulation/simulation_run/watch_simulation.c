#include "../simulation.h"

#include "event/t_event_log.h"

#include "simulation/philosopher/t_philosopher_state.h"
#include "time/instant.h"
#include "time/duration.h"
#include <string.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

static const char *state_action(t_philosopher_state st)
{
	if (st == HOLDING_LFORK)
		return "has taken a fork";
	if (st == EATING)
		return "is eating";
	if (st == SLEEPING)
		return "is sleeping";
	if (st == THINKING)
		return "is thinking";
	return (NULL);
}

static t_error init_variables(t_simulation *sim)
{
	const uint32_t	philosopher_count = sim->config.philosopher_count;
	t_instant		*last_meals;
	unsigned int	*meal_count;

	last_meals = malloc(sizeof (*last_meals) * philosopher_count);
	if (!last_meals)
		return (E_MALLOC);
	meal_count = malloc(sizeof (*meal_count) * philosopher_count);
	if (!meal_count)
	{
		free(last_meals);
		return (E_MALLOC);
	}
	sim->last_meals = last_meals;
	sim->meal_count = meal_count;
	memset(sim->last_meals, 0, sizeof (*last_meals) * philosopher_count);
	memset(sim->meal_count, 0, sizeof (*meal_count) * philosopher_count);
	return (NO_ERROR);
}

bool	any_philosophers_died(t_simulation *sim, t_instant last, uint32_t *dead_id)
{
	const uint32_t	philosopher_count = sim->config.philosopher_count;
	size_t			i;
	t_instant		last_meal;

	i = 0;
	while (i < philosopher_count)
	{
		if (sim->meal_count[i] == 0)
			last_meal = sim->simulation_start;
		else
			last_meal = sim->last_meals[i];
		if (duration_since_ms(last_meal, last) > sim->config.time_to_die)
		{
			*dead_id = i + 1;
			return (true);
		}
		i++;
	}
	return (false);
}

bool	all_philosophers_fed(t_simulation *sim)
{
	const uint32_t	philosopher_count = sim->config.philosopher_count;
	size_t			i;

	i = 0;
	while (i < philosopher_count)
	{
		if (sim->meal_count[i] < sim->config.min_meals)
			return (false);
		i++;
	}
	return (true);
}

bool	should_continue(t_simulation *sim)
{
	bool	all_meals_eaten;
	bool	thread_encountered_error;

	all_meals_eaten = sim->config.count_meals && all_philosophers_fed(sim);
	if (all_meals_eaten)
		return (false);
	pthread_mutex_lock(&sim->sim_state_mtx);
	thread_encountered_error = (sim->sim_state == SIMULATION_TERMINATED);
	pthread_mutex_unlock(&sim->sim_state_mtx);
	if (thread_encountered_error)
		return (false);
	return (true);
}

static bool process_incoming_events(t_simulation *sim)
{
	t_event event;
	uint32_t dead_philosopher;

	pthread_mutex_lock(&sim->event_log_mtx);
	bool got  = event_log_pop(&sim->event_log, &event);
	while (got)
	{
		t_duration	timestamp = duration_since_ms(sim->simulation_start, event.timestamp);

		if (event.new_state == EATING)
		{
			sim->last_meals[event.philosopher_id - 1] = event.timestamp;
			sim->meal_count[event.philosopher_id - 1] += 1;
		}
		if (event.new_state == EATING)
		{
			printf("%06lld %d %s\n", timestamp, event.philosopher_id, state_action(HOLDING_LFORK));
		}

		printf("%06lld %d %s\n", timestamp, event.philosopher_id, state_action(event.new_state));
		got  = event_log_pop(&sim->event_log, &event);
	}
	pthread_mutex_unlock(&sim->event_log_mtx);
	if (any_philosophers_died(sim, instant_now(), &dead_philosopher))
	{
		t_duration	timestamp = duration_since_ms(sim->simulation_start, instant_now());
		printf("%06lld %d died\n", timestamp, dead_philosopher);
		return true;
	}
	return (false);
}

t_error	watch_simulation(t_simulation *sim)
{
	t_error	err;
	bool	philosophers_died;

	err = init_variables(sim);
	if (err != NO_ERROR)
		return (err);
	philosophers_died = false;
	while (!philosophers_died && should_continue(sim))
		philosophers_died = process_incoming_events(sim);
	if (err != NO_ERROR)
		return (err);
	return (NO_ERROR);
}
