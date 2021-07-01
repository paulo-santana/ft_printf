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
 * Fetches all the data related to the current param to be printed based on the
 * placeholder.
 * Returns the amount of characters that were related to the param in case of
 * valid flags.
 * */

static int	get_flags(const char *str, t_param *param, va_list ap)
{
	char	*flags;
	int		chars;

	(void) ap;
	if (!*str)
		return (0);
	flags = "-0.*";
	chars = 0;
	while (is_flag(str[chars]))
	{
		if (str[chars] == '-')
			param->minus = 1;
		else if (str[chars] == '0')
			param->zero = 1;
		chars++;
	}
	return (chars);
}

static int	get_width(const char *str)
{
	int	width;

	width = ft_atoi(str);
	return (width);
}

static t_param	get_data(const char *str, va_list ap)
{
	t_param	param;
	int		offset;

	param.placeholder_len = 1;
	offset = get_flags(str, &param, ap);
	param.width = get_width(str + offset);
	while (ft_isdigit(str[offset]))
		offset++;
	param.str = get_str(str[offset], ap);
	param.precision = 0;
	param.placeholder_len += offset;
	return (param);
}

/* TODO: criar funções que verificam cada parte do placeholder
 * (flag, width, .precision, length e type) e gera os metadados necessarios 
 * para escrita na tela. */

static int	print_placeholder(const char **format, va_list ap,
		int *total_chars)
{
	t_param	param;
	int		chars_printed;

	param = get_data(*format + 1, ap);
	chars_printed = print_param(&param);
	free(param.str);
	*total_chars += chars_printed;
	*format = *format + param.placeholder_len;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int			chars_printed;
	va_list		ap;
	const char	*next_spec;

	chars_printed = 0;
	va_start(ap, format);
	while (format)
	{
		next_spec = ft_strchr(format, '%');
		if (next_spec)
		{
			write(1, format, next_spec - format);
			chars_printed += next_spec - format;
			print_placeholder(&next_spec, ap, &chars_printed);
			format = next_spec + 1;
		}
		else
		{
			ft_putstr_fd((char *)format, 1);
			chars_printed += ft_strlen(format);
			break ;
		}
	}
	va_end(ap);
	return (chars_printed);
}
