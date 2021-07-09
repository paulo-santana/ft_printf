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
	return (c == '0' || c == '-');
}

/**
 * Fetches all the data related to the current param to be printed based on the
 * placeholder.
 * Returns the amount of characters that were related to the param in case of
 * valid flags.
 * */

static int	get_flags(const char *str, t_param *param, va_list ap)
{
	int		chars;

	(void) ap;
	if (!*str)
		return (0);
	chars = 0;
	param->filler = ' ';
	while (is_flag(str[chars]))
	{
		if (str[chars] == '-')
			param->minus = 1;
		else if (str[chars] == '0')
		{
			param->zero = 1;
			param->filler = '0';
		}
		chars++;
	}
	return (chars);
}

static int	get_width(const char *str, t_param *param, va_list ap)
{
	int	width;
	int	offset;

	if (*str == '*')
		width = va_arg(ap, int);
	else
		width = ft_atoi(str);
	if (width < 0)
	{
		width = -width;
		param->minus = 1;
	}
	param->width = width;
	offset = 0;
	if (*str == '*')
		return (1);
	else
		while (ft_isdigit(*str++))
			offset++;
	return (offset);
}

static int	get_precision(const char *str, t_param *param, va_list ap)
{
	int	offset;

	param->has_precision = 0;
	offset = 0;
	if (*str++ == '.')
	{
		offset = 1;
		param->has_precision = 1;
		if (*str == '*')
			param->precision = va_arg(ap, int);
		else
			param->precision = ft_atoi(str);
		if (*str == '*')
			return (2);
		else
			while (ft_isdigit(*str++))
				offset++;
	}
	return (offset);
}

static t_param	*get_data(const char *str, va_list ap)
{
	t_param	*param;
	int		offset;

	param = ft_calloc(1, sizeof(t_param));
	if (param == NULL)
		return (NULL);
	param->specifier = '\0';
	param->placeholder_len = 1;
	offset = get_flags(str, param, ap);
	offset += get_width(str + offset, param, ap);
	offset += get_precision(str + offset, param, ap);
	get_str(str[offset], param, ap);
	param->str_len = ft_strlen(param->str);
	param->placeholder_len += offset;
	return (param);
}

/* TODO: criar funções que verificam cada parte do placeholder
 * (flag, width, .precision, length e type) e gera os metadados necessarios 
 * para escrita na tela. */

static int	print_placeholder(const char **format, va_list ap)
{
	t_param	*param;
	int		chars_printed;

	param = get_data(*format + 1, ap);
	chars_printed = print_param(param);
	*format = *format + param->placeholder_len;
	free(param->str);
	free(param);
	return (chars_printed);
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
			chars_printed += print_placeholder(&next_spec, ap);
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
