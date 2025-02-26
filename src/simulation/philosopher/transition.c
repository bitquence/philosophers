#include "t_philosopher.h"

#include "event/t_event.h"
#include "event/t_event_log.h"

#include <pthread.h>

t_error	philosopher_transition(t_philosopher *self, t_philosopher_state new)
{
	t_error	err;
	t_event	new_event;

	self->state = new;
	new_event = event_new(self->id, new);
	pthread_mutex_lock(self->event_log_mtx);
	err = event_log_append(self->event_log, new_event);
	pthread_mutex_unlock(self->event_log_mtx);
	return (err);
}
