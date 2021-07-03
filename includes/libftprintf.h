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
# include "libft.h"

typedef struct s_param
{
	int		precision;
	int		width;
	char	*str;
	int		minus;
	int		zero;
	size_t	placeholder_len;
	int		has_precision;
	char	specifier;
}			t_param;

void	get_str(char converter, t_param *param, va_list ap);
int		print_param(t_param *param);
void	handle_char(t_param *param, va_list ap);
void	handle_string(t_param *param, va_list ap);
void	handle_pointer(t_param *param, va_list ap);
void	handle_intd(t_param *param, va_list ap);
void	handle_inti(t_param *param, va_list ap);
void	handle_intu(t_param *param, va_list ap);
void	handle_hex(t_param *param, va_list ap);
void	handle_hex_upper(t_param *param, va_list ap);
void	handle_percentage(t_param *param);

#endif
