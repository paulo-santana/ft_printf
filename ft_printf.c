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
#include <stdarg.h>

static char	*char_to_str(int c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = (char)c;
	return (str);
}

static char	*int_to_pointer(ssize_t nbr)
{
	char	*hex;
	char	*address;

	if (nbr == 0)
	{
		address = ft_strdup("0x0");
	}
	else
	{
		hex = ft_itox(nbr);
		address = ft_strjoin("0x", hex);
		free(hex);
	}
	return (address);
}

static char	*get_str(char converter, va_list ap)
{
	char	*str;

	str = NULL;
	if (converter == 'c')
		str = char_to_str(va_arg(ap, int));
	else if (converter == 's')
		str = ft_strdup(va_arg(ap, char *));
	else if (converter == 'p')
		str = int_to_pointer(va_arg(ap, ssize_t));
	else if (converter == 'd')
		str = ft_itoa(va_arg(ap, int));
	else if (converter == 'i')
		str = ft_itoa(va_arg(ap, int));
	else
		str = ft_strdup("");
	return (str);
}

static int	is_flag(char c)
{
	return (c == '0' || c == '-' || c == '*');
}

static t_param	get_data(const char **str, int pos, va_list ap)
{
	t_param	param;

	if (is_flag((*str)[pos]))
		pos++;
	param.str = get_str((*str)[pos], ap);
	param.width = 0;
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
