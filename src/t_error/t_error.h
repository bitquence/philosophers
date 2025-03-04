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
	E_EXPECTED_NUM,
	E_OUT_OF_RANGE,
	E_UNMATCHED_PATTERN,
	// system calls
	E_PTHREAD_MUTEX_INIT,
	E_PTHREAD_MUTEX_LOCK,
	E_PTHREAD_MUTEX_UNLOCK,
	E_PTHREAD_CREATE,
	// library functions
	E_MALLOC,
}	t_error;

#endif // T_ERROR_H
