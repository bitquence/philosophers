#include "simulation.h"

#include <stdint.h>

static void	assign_single_fork(t_simulation *sim);
static void	assign_many_forks(t_simulation *sim);

void	assign_forks(t_simulation *sim)
{
	if (sim->config.philosopher_count == 1)
		return (assign_single_fork(sim));
	return (assign_many_forks(sim));
}

static void	assign_single_fork(t_simulation *sim)
{
	sim->philosophers[0].left = &sim->forks[0];
	sim->philosophers[0].right = NULL;
}

static void	assign_many_forks(t_simulation *sim)
{
	const uint32_t	count = sim->config.philosopher_count;
	size_t			i;

	i = 0;
	while (i + 1 < count)
	{
		sim->philosophers[i].left = &sim->forks[i];
		sim->philosophers[i].right = &sim->forks[i + 1];
		i++;
	}
	sim->philosophers[i].left = &sim->forks[i];
	sim->philosophers[i].right = &sim->forks[0];
}
