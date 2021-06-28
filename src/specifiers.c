/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psergio- <psergio-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 20:26:54 by psergio-          #+#    #+#             */
/*   Updated: 2021/06/26 20:26:54 by psergio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static char	*char_to_str(int c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = (char)c;
	return (str);
}

static char	*int_to_pointer(size_t nbr)
{
	char	*hex;
	char	*address;

	if (nbr == 0)
	{
		address = ft_strdup("0x0");
	}
	else
	{
		hex = ft_stox(nbr);
		address = ft_strjoin("0x", hex);
		free(hex);
	}
	return (address);
}

char	*get_str(char converter, va_list ap)
{
	char	*str;

	str = NULL;
	if (converter == 'c')
		str = char_to_str(va_arg(ap, int));
	else if (converter == 's')
		str = ft_strdup(va_arg(ap, char *));
	else if (converter == 'p')
		str = int_to_pointer(va_arg(ap, size_t));
	else if (converter == 'd')
		str = ft_itoa(va_arg(ap, int));
	else if (converter == 'i')
		str = ft_itoa(va_arg(ap, int));
	else if (converter == 'u')
		str = ft_uitoa(va_arg(ap, unsigned int));
	else if (converter == 'x')
		str = ft_itox(va_arg(ap, unsigned int));
	else if (converter == 'X')
		str = ft_strtoupper(ft_itox(va_arg(ap, unsigned int)));
	else if (converter == '%')
		str = ft_strdup("%");
	else
		str = ft_strdup("");
	return (str);
}
