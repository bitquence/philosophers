#include "../simulation.h"
#include "simulation/simulation_run/simulation_run.h"

t_error	simulation_run(t_simulation *sim)
{
	t_error err;

	err = initialize_threads(sim);
	if (err != NO_ERROR)
		return (err);
	err = watch_simulation(sim);
	end_simulation(sim);
	return (err);
}

