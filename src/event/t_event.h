#ifndef T_EVENT_H
# define T_EVENT_H

# include <stdint.h>
# include <sys/time.h>
# include "simulation/philosopher/t_philosopher_state.h"

typedef struct s_event {
	uint32_t			philosopher_id;
	struct timeval		timestamp;
	t_philosopher_state	new_state;
}	t_event;

#endif // T_EVENT_H
