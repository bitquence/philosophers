#include "t_event_log.h"

#include "t_event_node.h"

void	event_log_clear(t_event_log *log)
{
	t_event	event;

	while (event_log_pop(log, &event))
		;
}
