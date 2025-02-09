#include "t_philosopher.h"

#include <stdio.h>

void	*philosophize(t_philosopher *self)
{
	printf("%d | simulation status: %d\n", self->id, *self->sim_state);
	return (NULL);
}
