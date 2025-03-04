#include "simulation.h"

#include "t_error/t_error.h"

#include <stdlib.h>
#include <pthread.h>

void			assign_forks(t_simulation *sim);

static t_error	make_mutexes(t_simulation *sim, t_simulation_state state);
static t_error	make_forks(pthread_mutex_t **forks, uint32_t count);
static t_error	populate_philosophers(t_simulation *sim, uint32_t count);
static void		partially_destroy_forks(pthread_mutex_t **forks, uint32_t count);

t_error	simulation_new(t_config config, t_simulation *simulation_out)
{
	t_error	err;

	*simulation_out = (t_simulation){0};
	simulation_out->config = config;
	err = make_mutexes(simulation_out, SIMULATION_PENDING);
	if (err != NO_ERROR)
		return (err);
	err = make_forks(&simulation_out->forks, config.philosopher_count);
	if (err != NO_ERROR)
	{
		simulation_destroy(simulation_out);
		return (err);
	}
	err = populate_philosophers(simulation_out, config.philosopher_count);
	if (err != NO_ERROR)
	{
		simulation_destroy(simulation_out);
		return (err);
	}
	assign_forks(simulation_out);
	return (NO_ERROR);
}

static t_error	make_mutexes(t_simulation *sim, t_simulation_state state)
{
	int		ret;

	ret = pthread_mutex_init(&sim->sim_state_mtx, NULL);
	if (ret != 0)
		return (E_PTHREAD_MUTEX_INIT);
	ret = pthread_mutex_init(&sim->event_log_mtx, NULL);
	if (ret != 0)
	{
		pthread_mutex_destroy(&sim->sim_state_mtx);
		return (E_PTHREAD_MUTEX_INIT);
	}
	pthread_mutex_lock(&sim->sim_state_mtx);
	sim->sim_state = state;
	pthread_mutex_unlock(&sim->sim_state_mtx);
	return (NO_ERROR);
}

static t_error	populate_philosophers(t_simulation *sim, uint32_t count)
{
	size_t			i;

	sim->philosophers = malloc(sizeof(t_philosopher) * count);
	if (!sim->philosophers)
		return (E_MALLOC);
	i = 0;
	while (i < count)
	{
		sim->philosophers[i] = (t_philosopher){
			.id = i + 1,
			.config = &sim->config,
			.sim_state_mtx = &sim->sim_state_mtx,
			.sim_state = &sim->sim_state,
			.event_log_mtx = &sim->event_log_mtx,
			.event_log = &sim->event_log,
		};
		i++;
	}
	return (NO_ERROR);
}

static t_error	make_forks(pthread_mutex_t **forks, uint32_t count)
{
	size_t	i;
	int		ret;

	*forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!*forks)
		return (E_MALLOC);
	i = 0;
	while (i < count)
	{
		ret = pthread_mutex_init(&(*forks)[i], NULL);
		if (ret != 0)
		{
			partially_destroy_forks(forks, i);
			return (E_PTHREAD_MUTEX_INIT);
		}
		i++;
	}
	return (NO_ERROR);
}

static void	partially_destroy_forks(pthread_mutex_t **forks, uint32_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&(*forks)[i]);
		i++;
	}
	free(*forks);
	*forks = NULL;
}
