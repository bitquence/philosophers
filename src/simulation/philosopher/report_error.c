#include "t_philosopher.h"

#include "t_error/t_error.h"

#include <pthread.h>

void	philosopher_report_error(t_philosopher *self, t_error err)
{
	pthread_mutex_lock(self->last_error_mtx);
	self->last_error = err;
	pthread_mutex_unlock(self->last_error_mtx);
}
