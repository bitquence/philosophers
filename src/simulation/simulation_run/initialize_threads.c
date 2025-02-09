#include "../simulation.h"
#include "../philosopher/t_philosopher.h"
#include "simulation/t_simulation_state.h"

#include <pthread.h>
#include <stdlib.h>

typedef void	*(*t_pthread_routine)(void*);

static t_error	make_threads(t_simulation *sim, size_t *made_n_threads_out);
static void		destroy_threads(t_simulation *sim, size_t thread_count);

t_error	initialize_threads(t_simulation *sim)
{
	size_t	initialized_thread_count;
	t_error	err;

	pthread_mutex_lock(&sim->sim_state_mtx);
	err = make_threads(sim, &initialized_thread_count);
	if (err != NO_ERROR)
		sim->sim_state = SIMULATION_TERMINATED;
	else
		sim->sim_state = SIMULATION_STARTED;
	pthread_mutex_unlock(&sim->sim_state_mtx);
	if (err != NO_ERROR)
		destroy_threads(sim, initialized_thread_count);
	return (err);
}

static void	destroy_threads(t_simulation *sim, size_t thread_count)
{
	size_t	i;

	i = 0;
	while (i < thread_count)
	{
		pthread_join(sim->handles[i], NULL);
		i++;
	}
	free(sim->handles);
	sim->handles = NULL;
}

static t_error	make_threads(t_simulation *sim, size_t *made_n_threads_out)
{
	const size_t		count = sim->config.philosopher_count;
	size_t				i;
	pthread_t			*handle;
	t_philosopher		*philosopher;
	t_pthread_routine	routine;

	sim->handles = malloc(sizeof(pthread_t) * count);
	if (!sim->handles)
		return (E_MALLOC);
	i = 0;
	while (i < count)
	{
		handle = &sim->handles[i];
		philosopher = &sim->philosophers[i];
		routine = (t_pthread_routine)philosophize;
		if (pthread_create(handle, NULL, routine, philosopher) != 0)
		{
			*made_n_threads_out = i;
			return (E_PTHREAD_CREATE);
		}
		i++;
	}
	return (NO_ERROR);
}
