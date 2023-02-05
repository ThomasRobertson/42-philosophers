/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troberts <troberts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 00:16:58 by troberts          #+#    #+#             */
/*   Updated: 2023/01/23 01:50:49 by troberts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# ifndef RETURN_SUCCESS
#  define RETURN_SUCCESS EXIT_SUCCESS
# endif

# ifndef RETURN_FAILURE
#  define RETURN_FAILURE EXIT_FAILURE
# endif

# ifndef RETURN_ERROR
#  define RETURN_ERROR -1
# endif

# ifndef T_BOOL
#  define T_BOOL

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

# endif

#endif
