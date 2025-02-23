#include "t_event_log.h"
#include "event/t_event_node.h"

t_error	event_log_append(t_event_log *log, t_event event)
{
	t_event_node	*new_node;

	new_node = evl_new(event);
	if (!new_node)
		return (E_MALLOC);
	if (log->head == NULL || log->tail == NULL)
	{
		evl_push_link_back(&log->tail, new_node);
		log->head = log->tail;
		return (NO_ERROR);
	}
	evl_push_link_back(&log->tail, new_node);
	return (NO_ERROR);
}

bool	event_log_pop(t_event_log *log, t_event *event_out)
{
	t_event_node	*top;

	top = evl_pop_link_front(&log->head);
	if (top == NULL)
	{
		*event_out = (t_event){0};
		return (false);
	}
	if (log->head == NULL)
		log->tail = NULL;
	*event_out = top->event;
	evl_clear(&top);
	return (true);
}
