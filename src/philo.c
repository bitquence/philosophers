/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 03:24:57 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 03:26:00 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_error/t_error.h"
#include "config/config.h"
#include "simulation/simulation.h"

#include <stdlib.h>
#include <stdio.h>

static t_error	validate_config(const t_config *c)
{
	if (c->philosopher_count == 0)
		return E_BAD_USAGE;
	if (c->time_to_eat < 30)
		return E_BAD_USAGE;
	if (c->time_to_sleep < 30)
		return E_BAD_USAGE;
	return (NO_ERROR);
}

int	main(int argc, char *argv[])
{
	t_error			err;
	t_config		config;
	t_simulation	sim;

	err = config_from_args(argc, argv, &config);
	if (err != NO_ERROR)
		return (log_error(err), EXIT_FAILURE);
	err = validate_config(&config);
	if (err != NO_ERROR)
		return (log_error(err), EXIT_FAILURE);
	err = simulation_new(config, &sim);
	if (err != NO_ERROR)
		return (log_error(err), EXIT_FAILURE);
	err = simulation_run(&sim);
	simulation_destroy(&sim);
	if (err != NO_ERROR)
		return (log_error(err), EXIT_FAILURE);
}
