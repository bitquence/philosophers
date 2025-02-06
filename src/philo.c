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
#include "t_config/t_config.h"

#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char *argv[]) {
	t_error		err;
	t_config	config;

	err = config_from_args(argc, argv, &config);
	if (err != NO_ERROR)
		return (EXIT_FAILURE);
	printf("%s %u %u %u %u %u\n", argv[0], config.philosopher_count, config.time_to_die, config.time_to_eat, config.time_to_sleep, config.min_meals);
}
