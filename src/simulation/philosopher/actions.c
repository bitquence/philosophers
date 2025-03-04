#include "t_philosopher.h"
#include "./philosopher_internals.h"

#include "t_error/t_error.h"
#include "./t_philosopher_state.h"

#include <pthread.h>
#include <stdint.h>

#define ESTIMATED_SLEEP_OVERHEAD_MS 1


t_error	think_and_take_left_fork(t_philosopher *self)
{
	uint32_t duration;

	duration = self->config->time_to_sleep + self->config->time_to_eat;
	if ((!self->ate && self->id % 2 != 0) || (self->config->philosopher_count % 2 == 1))
	{
		if (philosopher_sleep(self, duration / 3.0f))
			return (NO_ERROR);
	}
	pthread_mutex_lock(self->left);
	return (philosopher_transition(self, HOLDING_LFORK));
}

t_error	take_right_fork(t_philosopher *self)
{
	if (!self->right)
	{
		unlock_mutexes_after_action(self);
		pthread_exit(NULL);
	}
	pthread_mutex_lock(self->right);
	return (philosopher_transition(self, EATING));
}

t_error	eat(t_philosopher *self)
{
	if (philosopher_sleep(self, self->config->time_to_eat))
		return (NO_ERROR);
	pthread_mutex_unlock(self->right);
	pthread_mutex_unlock(self->left);
	self->ate = true;
	return (philosopher_transition(self, SLEEPING));
}

t_error	sleep_to_go_again(t_philosopher *self)
{
	if (philosopher_sleep(self, self->config->time_to_sleep))
		return (NO_ERROR);
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
