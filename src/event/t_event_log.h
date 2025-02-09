#ifndef T_EVENT_LOG_H
# define T_EVENT_LOG_H

# include "t_error/t_error.h"

typedef struct s_event_node {
}	t_event_node;

typedef struct s_event_log {
	t_event_node	*head;
	t_event_node	*tail;
}	t_event_log;

#endif // T_EVENT_LOG_H
