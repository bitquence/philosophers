#ifndef T_PHILOSOPHER_H
# define T_PHILOSOPHER_H

# include "t_error/t_error.h"
# include "config/config.h"
# include "event/t_event_log.h"
# include "../t_simulation_state.h"
# include "./t_philosopher_state.h"

# include <pthread.h>
# include <stdint.h>

// all parameters are borrowed and should not be freed
typedef struct s_philosopher {
	uint32_t			id;
	const t_config		*config;
	t_philosopher_state	state;
	bool				ate;

	pthread_mutex_t		*sim_state_mtx;
	t_simulation_state	*sim_state;

	pthread_mutex_t		*event_log_mtx;
	t_event_log			*event_log;

	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
}	t_philosopher;

void		*philosophize(t_philosopher *self);

#endif // T_PHILOSOPHER_H
