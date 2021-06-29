/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:09:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/20 20:09:07 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_param
{
	int		precision;
	int		width;
	char	*str;
	int		minus;
	int		zero;
	size_t	placeholder_len;
}			t_param;

char	*get_str(char converter, va_list ap);

#endif
