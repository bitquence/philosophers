#include "../simulation.h"
#include "../t_simulation_state.h"
#include "./simulation_run_internals.h"

#include "t_error/t_error.h"
#include "time/instant.h"
#include "time/duration.h"

#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>

static bool	all_philosophers_fed(t_simulation *sim);
static bool	should_continue(t_simulation *sim);
static bool	any_philosophers_died(t_simulation *sim, t_instant last, uint32_t *dead_id);
static bool process_incoming_events(t_simulation *sim);

t_error	watch_simulation(t_simulation *sim)
{
	t_error	err;
	bool	philosophers_died;

	err = init_variables(sim);
	if (err != NO_ERROR)
		return (err);
	philosophers_died = false;
	while (!philosophers_died && should_continue(sim))
	{
		philosophers_died = process_incoming_events(sim);
		usleep(50);
	}
	return (NO_ERROR);
}

static bool	should_continue(t_simulation *sim)
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

static bool	all_philosophers_fed(t_simulation *sim)
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

static bool process_incoming_events(t_simulation *sim)
{
	t_event		event;
	uint32_t	dead_philosopher;
	bool		got;

	pthread_mutex_lock(&sim->event_log_mtx);
	got = event_log_pop(&sim->event_log, &event);
	while (got)
	{
		if (event.new_state == EATING)
		{
			sim->last_meals[event.philosopher_id - 1] = event.timestamp;
			sim->meal_count[event.philosopher_id - 1] += 1;
		}
		log_state_change(sim, event);
		got = event_log_pop(&sim->event_log, &event);
	}
	pthread_mutex_unlock(&sim->event_log_mtx);
	if (any_philosophers_died(sim, instant_now(), &dead_philosopher))
	{
		log_death(sim, instant_now(), dead_philosopher);
		return true;
	}
	return (false);
}

static bool	any_philosophers_died(t_simulation *sim, t_instant last, uint32_t *dead_id)
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
