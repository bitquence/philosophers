#ifndef SIMULATION_H
# define SIMULATION_H

# include "t_error/t_error.h"
# include "event/t_event_log.h"
# include "config/config.h"
# include "philosopher/t_philosopher.h"
# include "time/instant.h"
# include "./t_simulation_state.h"

# include <pthread.h>

typedef struct s_simulation {
	t_config			config;
	t_instant			simulation_start;
	pthread_mutex_t		*forks;
	pthread_t			*handles;
	t_philosopher		*philosophers;

	pthread_mutex_t		last_error_mtx;
	t_error				last_error;

	pthread_mutex_t		sim_state_mtx;
	t_simulation_state	sim_state;

	pthread_mutex_t		event_log_mtx;
	t_event_log			event_log;
}	t_simulation;

t_error	simulation_new(t_config config, t_simulation *simulation_out);
t_error	simulation_run(t_simulation *sim);
void	simulation_destroy(t_simulation *sim);

#endif // SIMULATION_H
