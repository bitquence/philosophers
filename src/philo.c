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

int	main(int argc, char *argv[])
{
	t_error			err;
	t_config		config;
	t_simulation	sim;

	err = config_from_args(argc, argv, &config);
	if (err != NO_ERROR)
		return (EXIT_FAILURE);
	err = simulation_new(config, &sim);
	if (err != NO_ERROR)
		return (EXIT_FAILURE);
	err = simulation_run(&sim);
	simulation_destroy(&sim);
	if (err != NO_ERROR)
		return (EXIT_FAILURE);
}
