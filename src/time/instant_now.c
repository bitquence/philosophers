#include "instant.h"

#include <sys/time.h>

t_instant	instant_now()
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((t_instant)now);
}
