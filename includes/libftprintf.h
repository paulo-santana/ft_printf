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
	size_t	width;
	char	*str;
	size_t	str_len;
	int		minus;
	int		zero;
	char	filler;
	size_t	placeholder_len;
	int		has_precision;
	char	specifier;
}			t_param;

void	get_str(char converter, t_param *param, va_list ap);
void	handle_char(t_param *param, va_list ap);
void	handle_string(t_param *param, va_list ap);
void	handle_pointer(t_param *param, va_list ap);
void	handle_intd(t_param *param, va_list ap);
void	handle_inti(t_param *param, va_list ap);
void	handle_intu(t_param *param, va_list ap);
void	handle_hex(t_param *param, va_list ap);
void	handle_hex_upper(t_param *param, va_list ap);
void	handle_percentage(t_param *param);

// output functions
int		fill_width(t_param *param);
int		fill_int_width(t_param *param);
int		print_param(t_param *param);
int		print_intd(t_param *param);
int		print_inti(t_param *param);
int		print_intu(t_param *param);
int		print_percent(t_param *param);

#endif
