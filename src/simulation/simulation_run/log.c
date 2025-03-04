#include "event/t_event.h"
#include "simulation/simulation.h"
#include "simulation/philosopher/t_philosopher_state.h"

#include "time/instant.h"
#include "time/duration.h"

#include <stdint.h>
#include <stdio.h>

static const char	*state_repr(t_philosopher_state st)
{
	if (st == HOLDING_LFORK)
		return ("has taken a fork");
	if (st == EATING)
		return ("is eating");
	if (st == SLEEPING)
		return ("is sleeping");
	if (st == THINKING)
		return ("is thinking");
	return (NULL);
}

void	log_state_change(t_simulation *sim, t_event event)
{
	unsigned long				timestamp;
	const uint32_t				philosopher_id = event.philosopher_id;
	const t_philosopher_state	new_state = event.new_state;
	const t_instant				at = event.timestamp;

	timestamp = duration_since_ms(sim->simulation_start, at);
	if (new_state == EATING)
		printf("%06ld %d %s\n", timestamp, philosopher_id, \
				state_repr(HOLDING_LFORK));
	printf("%06ld %d %s\n", timestamp, philosopher_id, state_repr(new_state));
}

void	log_death(t_simulation *sim, t_instant at,	uint32_t id)
{
	unsigned long	timestamp;

	timestamp = duration_since_ms(sim->simulation_start, at);
	printf("%06ld %d died\n", timestamp, id);
}
