/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_config.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:20:48 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 18:25:33 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./t_config.h"
#include "t_error/t_error.h"

t_error	config_from_args(int argc, char *argv[], t_config *cfg_out)
{
	if (argc != 5 && argc != 6)
		return (E_BAD_USAGE);
	(void)argv;
	(void)cfg_out;
	return (NO_ERROR);
}
