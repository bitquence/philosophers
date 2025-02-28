#include "t_philosopher.h"

#include "event/t_event.h"
#include "event/t_event_node.h"
#include "event/t_event_log.h"
#include "time/instant.h"

#include <pthread.h>

t_error	philosopher_transition(t_philosopher *self, t_philosopher_state new)
{
	t_event_node	*node;

	self->state = new;
	node = evl_new((t_event){.philosopher_id = self->id, .new_state = new});
	if (!node)
		return (E_MALLOC);
	node->event.timestamp = instant_now();
	pthread_mutex_lock(self->event_log_mtx);
	event_log_append_node(self->event_log, node);
	pthread_mutex_unlock(self->event_log_mtx);
	return (NO_ERROR);
}
