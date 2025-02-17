#ifndef T_EVENT_NODE_H
# define T_EVENT_NODE_H

# include "event/t_event.h"
# include "t_error/t_error.h"

typedef struct s_event_node {
	t_event				event;
	struct s_event_node	*next;
}	t_event_node;

t_event_node	*evl_new(t_event event);
t_event_node	*evl_pop_link_front(t_event_node **lst);
void			evl_push_link_front(t_event_node **lst, t_event_node *link);
void			evl_clear(t_event_node **lst);

#endif // T_EVENT_NODE_H
