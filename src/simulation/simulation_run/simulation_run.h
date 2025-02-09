#ifndef SIMULATION_RUN_H
# define SIMULATION_RUN_H

#include "../simulation.h"
#include "t_error/t_error.h"

t_error	initialize_threads(t_simulation *sim);
t_error	watch_simulation(t_simulation *sim);
void	end_simulation(t_simulation *sim);

#endif // SIMULATION_RUN_H
