#include "../simulation.h"

#include "t_error/t_error.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

t_error init_variables(t_simulation *sim)
{
	const uint32_t	philosopher_count = sim->config.philosopher_count;
	t_instant		*last_meals;
	unsigned int	*meal_count;

	last_meals = malloc(sizeof (*last_meals) * philosopher_count);
	if (!last_meals)
		return (E_MALLOC);
	meal_count = malloc(sizeof (*meal_count) * philosopher_count);
	if (!meal_count)
	{
		free(last_meals);
		return (E_MALLOC);
	}
	sim->last_meals = last_meals;
	sim->meal_count = meal_count;
	memset(sim->last_meals, 0, sizeof (*last_meals) * philosopher_count);
	memset(sim->meal_count, 0, sizeof (*meal_count) * philosopher_count);
	return (NO_ERROR);
}
