/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:16:21 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 18:20:08 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "t_error/t_error.h"

# include <stdbool.h>
# include <stdint.h>

typedef struct s_config {
	uint32_t		philosopher_count;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	bool			count_meals;
	uint32_t		min_meals;
}	t_config;

t_error	config_from_args(int argc, char *argv[], t_config *cfg_out);

#endif // CONFIG_H
