/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <gdosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:02:30 by gdosch            #+#    #+#             */
/*   Updated: 2024/10/30 16:09:15 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_putstr_ct(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[count])
		count += write(1, &s[count], 1);
	return (count);
}

static size_t	ft_putnbr_ct(unsigned long n, char type)
{
	const char	*base;
	size_t		count;

	count = 0;
	if (type == 'i' || type == 'u')
	{
		base = "0123456789";
		if (type == 'i' && (long)n < 0)
		{
			count += write(1, "-", 1);
			n = -(long)n;
		}
	}
	else if (type == 'p' || type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (n >= ft_strlen(base))
		count += ft_putnbr_ct(n / ft_strlen(base), type);
	ft_putchar_fd(base[n % ft_strlen(base)], 1);
	return (count + 1);
}

static size_t	ft_putptr_ct(const void *p)
{
	if (!p)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + ft_putnbr_ct((unsigned long)p, 'p'));
}

static size_t	ft_format(const char *format, va_list args)
{
	if (*format == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	else if (*format == 's')
		return (ft_putstr_ct(va_arg(args, const char *)));
	else if (*format == 'p')
		return (ft_putptr_ct(va_arg(args, const void *)));
	else if (*format == 'd' || *format == 'i')
		return (ft_putnbr_ct(va_arg(args, int), 'i'));
	else if (*format == 'u' || *format == 'x' || *format == 'X')
		return (ft_putnbr_ct(va_arg(args, unsigned int), *format));
	else if (*format == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	size_t		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_format(format, args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	return (va_end(args), count);
}