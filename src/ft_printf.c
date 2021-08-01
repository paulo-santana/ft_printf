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
#include <stdlib.h>

static int	print_placeholder(const char **format, va_list ap)
{
	t_param	*param;
	int		str_len;

	param = get_data(*format + 1, ap);
	if (param == NULL)
		return (-1);
	if (param->error)
	{
		free(param->str);
		free(param);
		return (-1);
	}
	str_len = param->str_len;
	*format = *format + param->placeholder_len;
	free(param->str);
	free(param);
	return (str_len);
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

struct s_output {
	int		size;
	char	*str;
};

typedef struct s_output	t_output;

int	join_param(t_output *output, char **format, va_list ap)
{
	t_param	*param;
	char	*tmp;
	int		offset;
	char	*placeholder;

	placeholder = *format;
	param = get_data(placeholder + 1, ap);
	if (param == NULL)
		return (-1);
	if (param->error)
	{
		free(param->str);
		free(param);
		output->size = -1;
		return (-1);
	}
	tmp = ft_memjoin(output->str, output->size, param->str, param->str_len);
	free(output->str);
	output->str = tmp;
	output->size += param->str_len;
	free(param->str);
	offset = param->placeholder_len + 1;
	*format = *format + offset;
	free(param);
	return (offset);
}

/* Joins the */

int	append_text(t_output *output, char **format)
{
	char	*tmp_str;
	char	*sub_str;
	int		size;
	char	*text;

	text = *format;
	tmp_str = ft_strchr(text, '%');
	if (tmp_str)
		size = tmp_str - text;
	else
		size = ft_strlen(text);
	sub_str = ft_substr(text, 0, size);
	*format = tmp_str;
	tmp_str = output->str;
	output->str = ft_memjoin(output->str, output->size, sub_str, size);
	output->size += size;
	free(tmp_str);
	free(sub_str);
	return (0);
}

t_output	*generate_output(char *format, va_list ap)
{
	t_output	*output;

	output = malloc(sizeof(t_output));
	if (output == NULL)
		return (NULL);
	output->size = 0;
	output->str = ft_calloc(1, 1);
	while (1)
	{
		append_text(output, &format);
		if (format == NULL)
			break ;
		join_param(output, &format, ap);
		if (format == NULL)
			break ;
	}
	return (output);
}

int	ft_vprintf(const char *format, va_list ap)
{
	t_output	*output;
	int			size;

	output = generate_output((char *)format, ap);
	if (output == NULL)
		return (-1);
	write(1, output->str, output->size);
	free(output->str);
	size = output->size;
	free(output);
	return (size);
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
