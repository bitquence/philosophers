#include "../simulation.h"
#include "simulation/t_simulation_state.h"

#include "t_error/t_error.h"

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

static void		set_terminated(pthread_mutex_t *m, t_simulation_state *state);
static t_error	wait_for_all_threads(pthread_t *handles, uint32_t count);

t_error	end_simulation(t_simulation *sim)
{
	t_error	result;

	set_terminated(&sim->sim_state_mtx, &sim->sim_state);
	result = wait_for_all_threads(sim->handles, sim->config.philosopher_count);
	free(sim->handles);
	sim->handles = NULL;
	return (result);
}

static void	set_terminated(pthread_mutex_t *m, t_simulation_state *state)
{
	pthread_mutex_lock(m);
	*state = SIMULATION_TERMINATED;
	pthread_mutex_unlock(m);
}

static t_error	wait_for_all_threads(pthread_t *handles, uint32_t count)
{
	size_t		i;
	uintptr_t	err;
	void		**err_location;

	i = 0;
	err = 0;
	err_location = (void **)&err;
	while (i < count)
	{
		pthread_join(handles[i], err_location);
		if (err != NO_ERROR)
			err_location = NULL;
		i++;
	}
	return ((t_error)err);
}
