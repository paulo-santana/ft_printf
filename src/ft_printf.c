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

static int	print_placeholder(const char **format, va_list ap)
{
	t_param	*param;
	int		chars_printed;

	param = get_data(*format + 1, ap);
	if (param == NULL)
		return (-1);
	if (param->error)
	{
		free(param->str);
		free(param);
		return (-1);
	}
	chars_printed = print_param(param);
	*format = *format + param->placeholder_len;
	free(param->str);
	free(param);
	return (chars_printed);
}

void	run_printers(const char *format, va_list ap, int *total_chars)
{
	const char	*next_spec;
	int			chars_printed;

	while (format)
	{
		next_spec = ft_strchr(format, '%');
		if (next_spec)
		{
			write(1, format, next_spec - format);
			*total_chars += next_spec - format;
			chars_printed = print_placeholder(&next_spec, ap);
			if (chars_printed == -1)
				return ;
			*total_chars += chars_printed;
			format = next_spec + 1;
		}
		else
		{
			ft_putstr_fd((char *)format, 1);
			*total_chars += ft_strlen(format);
			format = NULL;
		}
	}
}

int	ft_vprintf(const char *format, va_list ap)
{
	int	chars_printed;

	chars_printed = 0;
	run_printers(format, ap, &chars_printed);
	return (chars_printed);
}

int	ft_printf(const char *format, ...)
{
	int			chars_printed;
	va_list		ap;

	chars_printed = 0;
	va_start(ap, format);
	chars_printed = ft_vprintf(format, ap);
	va_end(ap);
	return (chars_printed);
}
