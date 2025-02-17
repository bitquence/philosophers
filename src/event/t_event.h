#ifndef T_EVENT_H
# define T_EVENT_H

# include <stdint.h>
# include <sys/time.h>

typedef enum e_event_type {
	STARTED_EATING
}	t_event_type;

typedef struct s_event {
	uint32_t		philosopher_id;
	struct timeval	timestamp;
	t_event_type	type;
}	t_event;

#endif // T_EVENT_H
