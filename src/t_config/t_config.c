/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:20:48 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 18:30:41 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_config.h"
#include "t_error/t_error.h"

#include <stddef.h>

t_error	parse_uint32(const char *str, uint32_t *result_out);

t_error	config_from_args(int argc, char *argv[], t_config *cfg_out)
{
	t_error	err;

	if (argc != 5 && argc != 6)
		return (E_BAD_USAGE);
	*cfg_out = (t_config){0};
	err = parse_uint32(argv[1], &cfg_out->philosopher_count);
	if (err != NO_ERROR)
		return (err);
	err = parse_uint32(argv[2], &cfg_out->time_to_die);
	if (err != NO_ERROR)
		return (err);
	err = parse_uint32(argv[3], &cfg_out->time_to_eat);
	if (err != NO_ERROR)
		return (err);
	err = parse_uint32(argv[4], &cfg_out->time_to_sleep);
	if (err != NO_ERROR)
		return (err);
	cfg_out->count_meals = (argc == 6);
	if (cfg_out->count_meals)
		err = parse_uint32(argv[4], &cfg_out->min_meals);
	return (err);
}
