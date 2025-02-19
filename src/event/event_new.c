#include "t_event.h"

#include <stdint.h>
#include <sys/time.h>
#include "simulation/philosopher/t_philosopher_state.h"

t_event	event_new(uint32_t id, t_philosopher_state new)
{
	t_event	event;

	event = (t_event){0};
	event.philosopher_id = id;
	gettimeofday(&event.timestamp, NULL);
	event.new_state = new;
	return (event);
}
