#include "../simulation.h"
#include "simulation/t_simulation_state.h"

#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

static void	set_terminated(pthread_mutex_t *m, t_simulation_state *state);
static void	wait_for_all_threads(pthread_t *handles, uint32_t count);

void	end_simulation(t_simulation *sim)
{
	set_terminated(&sim->sim_state_mtx, &sim->sim_state);
	wait_for_all_threads(sim->handles, sim->config.philosopher_count);
	free(sim->handles);
	sim->handles = NULL;
}

static void	set_terminated(pthread_mutex_t *m, t_simulation_state *state)
{
	pthread_mutex_lock(m);
	*state = SIMULATION_TERMINATED;
	pthread_mutex_unlock(m);
}

static void	wait_for_all_threads(pthread_t *handles, uint32_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		pthread_join(handles[i], NULL);
		i++;
	}
}
