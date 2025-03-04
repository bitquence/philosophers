#ifndef SIMULATION_RUN_INTERNALS_H
# define SIMULATION_RUN_INTERNALS_H

#include "simulation/simulation.h"

#include "event/t_event.h"
#include "time/instant.h"

#include <stdint.h>

void	log_state_change(t_simulation *sim, t_event event);
void	log_death(t_simulation *sim, t_instant at,	uint32_t id);

#endif // SIMULATION_RUN_INTERNALS_H
