#include "../simulation.h"
#include "simulation/simulation_run/simulation_run.h"

t_error	simulation_run(t_simulation *sim)
{
	t_error err;
	t_error result;

	err = initialize_threads(sim);
	if (err != NO_ERROR)
		return (err);
	err = watch_simulation(sim);
	result = end_simulation(sim);
	if (err != NO_ERROR)
		return (err);
	return (result);
}

