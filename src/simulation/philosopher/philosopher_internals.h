#ifndef PHILOSOPHER_INTERNALS_H
# define PHILOSOPHER_INTERNALS_H

# include "./t_philosopher.h"

bool	simulation_pending(t_philosopher *self);
bool	simulation_started(t_philosopher *self);
bool	simulation_terminated(t_philosopher *self);

void	philosopher_report_error(t_philosopher *self, t_error err);
void	philosopher_sleep(t_philosopher *self, uint32_t ms_duration);
t_error	philosopher_transition(t_philosopher *self, t_philosopher_state new);

t_error	think_and_take_left_fork(t_philosopher *self);
t_error	take_right_fork(t_philosopher *self);
t_error	eat(t_philosopher *self);
t_error	sleep_to_go_again(t_philosopher *self);
void	unlock_mutexes_after_action(t_philosopher *self);

#endif // PHILOSOPHER_INTERNALS_H
