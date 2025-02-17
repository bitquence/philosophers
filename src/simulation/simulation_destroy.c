#include "simulation.h"

#include "event/t_event_log.h"

#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

void		event_log_clear(t_event_log **self);

static void	destroy_forks(pthread_mutex_t **forks, uint32_t count);
static void	destroy_arrays(pthread_t **handles, t_philosopher **philosophers);
static void	destroy_mutexes(t_simulation *sim);

void	simulation_destroy(t_simulation *sim)
{
	//event_log_clear(&sim->event_log);
	destroy_forks(&sim->forks, sim->config.philosopher_count);
	destroy_arrays(&sim->handles, &sim->philosophers);
	destroy_mutexes(sim);
}

static void	destroy_forks(pthread_mutex_t **forks, uint32_t count)
{
	size_t	i;

	if (!*forks)
		return ;
	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
	*forks = NULL;
}

static void	destroy_arrays(pthread_t **handles, t_philosopher **philosophers)
{
	free(*handles);
	*handles = NULL;
	free(*philosophers);
	*philosophers = NULL;
}

static void	destroy_mutexes(t_simulation *sim)
{
	pthread_mutex_destroy(&sim->last_error_mtx);
	pthread_mutex_destroy(&sim->sim_state_mtx);
	pthread_mutex_destroy(&sim->event_log_mtx);
}
