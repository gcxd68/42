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

#include "libft.h"

static size_t	ft_putstr_ct(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[len])
		len += write(1, &s[len], 1);
	return (len);
}

static size_t	ft_putnbr_ct(long n, char type)
{
	char	*base;
	size_t	count;

	base = NULL;
	count = 0;
	if (type == 'd' || type == 'u')
	{
		base = "0123456789";
		if (type == 'd' && n < 0)
		{
			write(1, "-", 1);
			n -= 2 * n;
			count++;
		}
	}
	else if (type == 'p' || type == 'x')
		base = "0123456789abcdef";
	else if (type == 'X')
		base = "0123456789ABCDEF";
	if (n >= (long)ft_strlen(base))
		count += ft_putnbr_ct(n / ft_strlen(base), type);
	ft_putchar_fd(base[n % ft_strlen(base)], 1);
	return (count + 1);
}

static size_t	ft_format(const char *format, va_list args)
{
	const void	*p;

	if (*(format + 1) == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1), 1);
	else if (*(format + 1) == 's')
		return (ft_putstr_ct((char *)va_arg(args, const char *)));
	else if (*(format + 1) == 'p')
	{
		p = va_arg(args, void *);
		if (!p)
			return (ft_putstr_ct("(nil)"));
		else
			return (ft_putstr_ct("0x") + ft_putnbr_ct((unsigned long)p, 'p'));
	}
	else if (*(format + 1) == 'd' || *(format + 1) == 'i')
		return (ft_putnbr_ct(va_arg(args, int), 'd'));
	else if (*(format + 1) == 'u')
		return (ft_putnbr_ct(va_arg(args, unsigned int), 'u'));
	else if (*(format + 1) == 'x')
		return (ft_putnbr_ct(va_arg(args, unsigned int), 'x'));
	else if (*(format + 1) == 'X')
		return (ft_putnbr_ct(va_arg(args, unsigned int), 'X'));
	else if (*(format + 1) == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			count += ft_format(format, args);
			format ++;
		}
		else
			count += write(1, format, 1);
		format++;
	}
	return (va_end(args), count);
}

int main(void)
{
	int		di = -42;
	int		u = -1;
	int		*p = &di;
	char	*s = NULL;
	int		xl = -3;
	int		xu = -5;

	printf("printf : \n");
	printf("len = %d\n", printf("s%s%ct %p %d %s %p %i %u %x %X %% %s\n", "al", 'u', p, di, s, s, di, u, xl, xu, "jio"));
	printf("\n");
	printf("ft_printf : \n");
	printf("len = %d\n", ft_printf("s%s%ct %p %d %s %p %i %u %x %X %% %s\n", "al", 'u', p, di, s, s, di, u, xl, xu, "jio"));
	return (0);
}

// TESTER AVEC DES NULL + TESTEUR