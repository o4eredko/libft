/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yochered <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 10:14:10 by yochered          #+#    #+#             */
/*   Updated: 2018/11/26 10:14:13 by yochered         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static int	handle_expression(va_list ap, const char **format)
{
	t_params	params;
	int			ret;
	int			index;
	int			(*f[10])(va_list, t_params*);

	ret = 0;
	fill_function_arr(f);
	(*format)++;
	if (!**format || !allowed_symbols((char*)*format))
		return (0);
	init_params(&params);
	reach_type(format, &params, ap);
	index = type_id(**format, &params);
	if (index != -1 || **format == '%' || ft_isalpha(**format))
	{
		ret += index == -1 ?
			print_percent(**format, &params) : f[index](ap, &params);
		(*format)++;
	}
	else
		ret += print_percent(0, &params);
	return (ret);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;
	char		*next_arg;

	ret = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
			ret += handle_expression(ap, &format);
		else
		{
			if (!(next_arg = ft_strchr(format, '%')))
			{
				next_arg = (char*)format;
				next_arg += ft_strlen(format);
			}
			write(1, format, next_arg - format);
			ret += next_arg - format;
			format += next_arg - format;
		}
	}
	va_end(ap);
	return (ret);
}
