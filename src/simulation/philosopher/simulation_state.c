#include "t_philosopher.h"

#include "simulation/t_simulation_state.h"

#include <stdbool.h>
#include <pthread.h>

static t_simulation_state	simulation_state(t_philosopher *self)
{
	t_simulation_state	value;

	pthread_mutex_lock(self->sim_state_mtx);
	value = *self->sim_state;
	pthread_mutex_unlock(self->sim_state_mtx);
	return (value);
}

bool	simulation_pending(t_philosopher *self)
{
	return (simulation_state(self) == SIMULATION_PENDING);
}

bool	simulation_started(t_philosopher *self)
{
	return (simulation_state(self) == SIMULATION_STARTED);
}

bool	simulation_terminated(t_philosopher *self)
{
	return (simulation_state(self) == SIMULATION_TERMINATED);
}
