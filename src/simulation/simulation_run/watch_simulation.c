#include "../simulation.h"

#include "event/t_event_log.h"

#include "simulation/philosopher/t_philosopher_state.h"
#include "time/instant.h"
#include "time/duration.h"
#include <unistd.h>

#include <stdio.h>

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

t_error	watch_simulation(t_simulation *sim)
{
	while (1)
	{
		pthread_mutex_lock(&sim->event_log_mtx);
		t_event event;
		bool has = event_log_pop(&sim->event_log, &event);
		while (has)
		{
			suseconds_t	timestamp = duration_since( sim->simulation_start, event.timestamp ) / 1000l;
			if (event.new_state == EATING)
				printf("%06d %d %s\n", timestamp, event.philosopher_id, state_action(HOLDING_LFORK));
			printf("%06d %d %s\n", timestamp, event.philosopher_id, state_action(event.new_state));
			has = event_log_pop(&sim->event_log, &event);
		}
		pthread_mutex_unlock(&sim->event_log_mtx);
		usleep(1 * 1000);
	}
	return (NO_ERROR);
}
