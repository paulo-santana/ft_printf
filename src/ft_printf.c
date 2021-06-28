/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:03:07 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/22 17:44:45 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static int	is_flag(char c)
{
	return (c == '0' || c == '-' || c == '*');
}

/**
 * Fetches all the data related to the current param to be printed
 * */

static void	get_flags(const char *str, t_param *param, va_list ap)
{
	char	*flags;

	(void) ap;
	if (!*str)
		return ;
	flags = "-0.*";
	while (is_flag(*str))
	{
		if (*str == '-')
			param->minus = 1;
		else if (*str == '0')
			param->zero = 1;
		str++;
	}
}

static int	get_width(const char *str)
{
	int	width;

	width = ft_atoi(str);
	return (width);
}

static t_param	get_data(const char **str, int pos, va_list ap)
{
	t_param	param;

	get_flags(*str + pos, &param, ap);
	if (is_flag((*str)[pos]))
		(*str)++;
	param.str = get_str((*str)[pos], ap);
	param.width = get_width((*str) + pos);
	param.precision = 0;
	return (param);
}

/* TODO: criar funções que verificam cada parte do placeholder
 * (flag, width, .precision, length e type) e gera os metadados necessarios 
 * para escrita na tela. */

static int	print_placeholder(const char **format, int pos, va_list ap)
{
	char	param_type;
	t_param	param;
	int		chars_printed;

	param_type = (*format)[pos + 1];
	param = get_data(format, pos + 1, ap);
	ft_putstr_fd(param.str, 1);
	(*format)++;
	chars_printed = ft_strlen(param.str);
	free(param.str);
	return (chars_printed);
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		chars_printed;
	va_list	ap;

	i = 0;
	chars_printed = 0;
	va_start(ap, format);
	while (format[i])
	{
		if (format[i] == '%')
			chars_printed += print_placeholder(&format, i++, ap);
		else
		{
			ft_putchar_fd(format[i++], 1);
			chars_printed++;
		}
	}
	return (chars_printed);
}
