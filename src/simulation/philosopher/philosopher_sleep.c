#include "t_philosopher.h"
#include "./philosopher_internals.h"

#include "time/instant.h"
#include "time/duration.h"

#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

// sleep 5ms before checking if sleep duration has elapsed
#define SLEEP_INTERVAL_USECONDS 5000

void	philosopher_sleep(t_philosopher *self, uint32_t ms_duration)
{
	struct timeval	start;
	struct timeval	now;
	uint64_t		duration;

	duration = ms_duration * 1000;
	if (SLEEP_INTERVAL_USECONDS > duration)
		return (void)usleep(duration);
	start = instant_now();
	while (1)
	{
		if (simulation_terminated(self))
			break;
		now = instant_now();
		if (duration_since(start, now) > duration)
			break;
		usleep(SLEEP_INTERVAL_USECONDS);
	}
}
