#include "t_philosopher.h"
#include "philosopher_internals.h"

#include "t_error/t_error.h"
#include "simulation/t_simulation_state.h"
#include "t_philosopher_state.h"

#include <unistd.h>
#include <pthread.h>
#include <stdio.h> // tmp

static t_error	run_philosopher_loop(t_philosopher *self);
static void		terminate_simulation(t_philosopher *self);

void	*philosophize(t_philosopher *self)
{
	t_error	err;

	while (simulation_pending(self))
		usleep(1000);
	err = run_philosopher_loop(self);
	if (err != NO_ERROR && err != E_NO_FORKS)
	{
		terminate_simulation(self);
		return ((void *)err);
	}
	return ((void *)NO_ERROR);
}

static void	terminate_simulation(t_philosopher *self)
{
	pthread_mutex_lock(self->sim_state_mtx);
	*self->sim_state = SIMULATION_TERMINATED;
	pthread_mutex_unlock(self->sim_state_mtx);
}

static t_error run_philosopher_loop(t_philosopher *self)
{
	t_error	err;

	err = NO_ERROR;
	self->state = THINKING;
	while (simulation_started(self) && err == NO_ERROR)
	{
		if (self->state == THINKING)
			err = think_and_take_left_fork(self);
		else if (self->state == HOLDING_LFORK)
			err = take_right_fork(self);
		else if (self->state == EATING)
			err = eat(self);
		else if (self->state == SLEEPING)
			err = sleep_to_go_again(self);
		else
			err = E_UNMATCHED_PATTERN;
	}
	unlock_mutexes_after_action(self);
	return (err);
}

