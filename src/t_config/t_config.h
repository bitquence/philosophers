/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_config.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:16:21 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 18:20:08 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CONFIG_H
# define T_CONFIG_H

# include "t_error/t_error.h"

# include <stdbool.h>
# include <stdint.h>

typedef struct s_config {
	int32_t		philosopher_count;
	int32_t		time_to_die;
	int32_t		time_to_eat;
	int32_t		time_to_sleep;
	bool		count_meals;
	int32_t		min_meals;
}	t_config;

t_error	config_from_args(int argc, char *argv[], t_config *cfg_out);

#endif // T_CONFIG_H
