#include "duration.h"

t_duration	duration_since(t_instant from, t_instant to)
{
	uint64_t	d;

	d = to.tv_usec - from.tv_usec;
	d += (to.tv_sec - from.tv_sec) * 1000 * 1000;
	return (t_duration)d;
}
