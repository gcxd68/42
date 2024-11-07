/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:46:36 by gdosch            #+#    #+#             */
/*   Updated: 2024/11/05 11:46:38 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putstr_ct(const char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (s[count])
	{
		if (write(1, &s[count], 1) < 0)
			return (-1);
		count++;
	}
	return (count);
}

static int	ft_putnbr_ct(unsigned long n, const char *format, char *base)
{
	int			count;
	int			ret;

	if (*format == 'x')
		base = "0123456789abcdef";
	if (*format == 'X')
		base = "0123456789ABCDEF";
	count = 0;
	if ((*format == 'i' || *format == 'd') && (long)n < 0)
	{
		if (write(1, "-", 1) < 0)
			return (-1);
		count++;
		n = -(long)n;
	}
	if (n >= ft_strlen(base))
	{
		ret = ft_putnbr_ct(n / ft_strlen(base), format, base);
		if (ret < 0)
			return (-1);
		count += ret;
	}
	if (write(1, &base[n % ft_strlen(base)], 1) < 0)
		return (-1);
	return (count + 1);
}

static int	ft_putptr_ct(const void *p, const char *format)
{
	int	count;

	if (!p)
	{
		if (write(1, "(nil)", 5) < 0)
			return (-1);
		return (5);
	}
	if (write(1, "0x", 2) < 0)
		return (-1);
	count = ft_putnbr_ct((unsigned long)p, format, "0123456789abcdef");
	if (count < 0)
		return (-1);
	return (count + 2);
}

static int	ft_format(const char *format, va_list args)
{
	if (*format == 'c' || *format == '%')
	{
		if (*format == 'c')
			if (write(1, &(char){(char)va_arg(args, int)}, 1) < 0)
				return (-1);
		if (*format == '%')
			if (write(1, "%", 1) < 0)
				return (-1);
		return (1);
	}
	else if (*format == 's')
		return (ft_putstr_ct(va_arg(args, const char *)));
	else if (*format == 'p')
		return (ft_putptr_ct(va_arg(args, const void *), format));
	else if (*format == 'i' || *format == 'd')
		return (ft_putnbr_ct(va_arg(args, int), format, "0123456789"));
	else if (*format == 'u' || *format == 'x' || *format == 'X')
		return (ft_putnbr_ct(va_arg(args, unsigned int), format, "0123456789"));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		ret;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			ret = ft_format(format, args);
		}
		else
			ret = write(1, format, 1);
		if (ret < 0)
			return (va_end(args), -1);
		count += ret;
		format++;
	}
	return (va_end(args), count);
}
