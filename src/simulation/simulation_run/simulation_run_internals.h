#ifndef SIMULATION_RUN_INTERNALS_H
# define SIMULATION_RUN_INTERNALS_H

#include "simulation/simulation.h"

#include "t_error/t_error.h"
#include "event/t_event.h"
#include "time/instant.h"

#include <stdint.h>

void	log_state_change(t_simulation *sim, t_event event);
void	log_death(t_simulation *sim, t_instant at,	uint32_t id);

t_error	init_variables(t_simulation *sim);

#endif // SIMULATION_RUN_INTERNALS_H
