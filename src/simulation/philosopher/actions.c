#include "t_philosopher.h"
#include "./philosopher_internals.h"

#include "t_error/t_error.h"
#include "./t_philosopher_state.h"

#include <pthread.h>

t_error	think_and_take_left_fork(t_philosopher *self)
{
	float duration = ( (float)self->config->time_to_die / 5 );
	philosopher_sleep(self, ( duration / self->config->philosopher_count ) * self->id);
	pthread_mutex_lock(self->left);
	return (philosopher_transition(self, HOLDING_LFORK));
}

t_error	take_right_fork(t_philosopher *self)
{
	pthread_mutex_lock(self->right);
	return (philosopher_transition(self, EATING));
}

t_error	eat(t_philosopher *self)
{
	philosopher_sleep(self, self->config->time_to_eat);
	pthread_mutex_unlock(self->right);
	pthread_mutex_unlock(self->left);
	return (philosopher_transition(self, SLEEPING));
}

t_error	sleep_to_go_again(t_philosopher *self)
{
	philosopher_sleep(self, self->config->time_to_sleep);
	return (philosopher_transition(self, THINKING));
}

void	unlock_mutexes_after_action(t_philosopher *self)
{
	if (self->state == HOLDING_LFORK)
		pthread_mutex_unlock(self->left);
	else if (self->state == EATING)
	{
		pthread_mutex_unlock(self->left);
		pthread_mutex_unlock(self->right);
	}
}
