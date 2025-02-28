#ifndef T_EVENT_LOG_H
# define T_EVENT_LOG_H


# include "t_error/t_error.h"
# include "event/t_event.h"
# include "./t_event_node.h"

# include <stdbool.h>

typedef struct s_event_log {
	t_event_node	*head;
	t_event_node	*tail;
}	t_event_log;

t_error	event_log_append(t_event_log *log, t_event event);
void	event_log_append_node(t_event_log *log, t_event_node *new_node);
bool	event_log_pop(t_event_log *log, t_event *event_out);

#endif // T_EVENT_LOG_H
