#include "t_philosopher.h"
#include "./philosopher_internals.h"

#include "time/instant.h"
#include "time/duration.h"

#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

// sleep 5ms before checking if sleep duration has elapsed
#define SLEEP_INTERVAL_USECONDS 5000

static uint32_t time_until_sleep_ends(t_instant start, t_instant now, uint32_t duration)
{
	uint32_t const since_start = duration_since(start, now);
	if (duration < since_start)
		return (0);
	return (duration - since_start);
}

typedef bool	t_should_exit;

t_should_exit	philosopher_sleep(t_philosopher *self, uint32_t ms_duration)
{
	struct timeval	start;
	struct timeval	now;
	uint64_t		duration;

	duration = ms_duration * 1000;
	if (SLEEP_INTERVAL_USECONDS > duration)
	{
		usleep(duration);
		return (false);
	}
	start = instant_now();
	while (1)
	{
		if (simulation_terminated(self))
			return (true);
		now = instant_now();
		if ((uint64_t)duration_since(start, now) > duration)
			return (false);
		uint32_t d = time_until_sleep_ends(start, now, duration);
		if (SLEEP_INTERVAL_USECONDS > d)
		{
			usleep(d);
			return (false);
		}
		usleep(SLEEP_INTERVAL_USECONDS);
	}
}
