/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_error.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamar <jamar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:15:33 by jamar             #+#    #+#             */
/*   Updated: 2025/02/05 18:26:25 by jamar            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ERROR_H
# define T_ERROR_H

typedef enum e_error {
	NO_ERROR = 0,
	E_BAD_USAGE,
	E_INVALID_ARGUMENT,
	E_OUT_OF_RANGE,
}	t_error;

#endif // T_ERROR_H
