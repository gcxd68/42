/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:27 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/05 12:55:29 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int	ft_atoi_psc(const char *nptr, int *arr)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		if ((sign == 1 && res > (unsigned)INT_MAX) || (sign == -1 && res > (unsigned)(-(long)INT_MIN)))
		{
			ft_printf("Error\n");
			free(arr);
			arr = 0;
			exit (1);
		}
		nptr++;
	}
	if (ft_isdigit(*nptr) == 0 && *nptr != '\0')
	{
		ft_printf("Error\n");
		free(arr);
		arr = 0;
		exit (1);
	}
	return ((int)res * sign);
}

void	ft_sx(int *arr)
{
	int	tmp;

	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}

void	ft_px(int *arr1, int *arr2, size_t *size_a1, size_t *size_a2)
{
	size_t	i;

	i = *size_a1;
	while (i > 0)
	{
		arr1[i] = arr1[i - 1];
		i--;
	}
	arr1[0] = arr2[0];
	i = 0;
	while (i < *size_a2 - 1)
	{
		arr2[i] = arr2[i + 1];
		i++;
	}
	*size_a1 += 1;
	*size_a2 -= 1;
}

void	ft_rx(int *arr, size_t *size)
{
	int		tmp;
	size_t	i;

	tmp = arr[0];
	i = 0;
	while (i < *size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = tmp;
}

void	ft_rrx(int *arr, size_t *size)
{
	int		tmp;
	size_t	i;

	i = *size - 1;
	tmp = arr[i];
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = tmp;
}

size_t	ft_stdin(int *a, int *b, size_t *size_a)
{
	char	*line;
	size_t	size_b;

	size_b = 0;
	while ((line = get_next_line(0)))
	{
		if (ft_strncmp(line, "sa\n", 3) == 0)
			ft_sx(a);
		else if (ft_strncmp(line, "sb\n", 3) == 0)
			ft_sx(b);
		else if (ft_strncmp(line, "ss\n", 3) == 0)
		{
			ft_sx(a);
			ft_sx(b);
		}
		else if (ft_strncmp(line, "pa\n", 3) == 0)
			ft_px(a, b, size_a, &size_b);
		else if (ft_strncmp(line, "pb\n", 3) == 0)
			ft_px(b, a, &size_b, size_a);
		else if (ft_strncmp(line, "ra\n", 3) == 0)
			ft_rx(a, size_a);
		else if (ft_strncmp(line, "rb\n", 3) == 0)
			ft_rx(b, &size_b);
		else if (ft_strncmp(line, "rr\n", 3) == 0)
		{
			ft_rx(a, size_a);
			ft_rx(b, &size_b);
		}
		else if (ft_strncmp(line, "rra\n", 4) == 0)
			ft_rrx(a, size_a);
		else if (ft_strncmp(line, "rrb\n", 4) == 0)
			ft_rrx(b, &size_b);
		else if (ft_strncmp(line, "rrr\n", 4) == 0)
		{
			ft_rrx(a, size_a);
			ft_rrx(b, &size_b);
		}
		else
		{
			ft_printf("Error\n");
			free(a);
			a = 0;
			free(b);
			b = 0;
			exit (1);
		}
		free(line);
	}
	return (size_b);
}

int	main(int argc, char *argv[])
{
	int	*a;
	int	*b;
	size_t	size_a;
	size_t	size_b;
	size_t	i;
	size_t	j;

	size_a = argc - 1;
	if (argc < 2)
		return (1);

	a = ft_calloc(size_a, sizeof(int));
	if (!a)
		return (1);

	i = 0;
	while (i < size_a)
	{
		a[i] = ft_atoi_psc(argv[i + 1], a);
		i++;
	}

	i = 0;
	while (i < size_a - 1)
	{
		j = i + 1;
		while (j < size_a)
		{
			if (a[i] == a[j])
				return (ft_printf("Error\n"), free(a), a = 0, 1);
			j++;
		}
		i++;
	}
	
	b = ft_calloc(size_a, sizeof(int));
	if (!b)
		return (free(a), a = 0, 1);

	size_b = ft_stdin(a, b, &size_a);

	i = 0;
	ft_printf("\n");
	ft_printf("PILE A\n");
	while (i < size_a)
	{
		ft_printf("Ligne %i : %i\n", i, a[i]);
		i++;
	}
	i = 0;
	ft_printf("\n");
	ft_printf("PILE B\n");
	while (i < size_b)
	{
		ft_printf("Ligne %i : %i\n", i, b[i]);
		i++;
	}

	ft_printf("\n");

	i = 0;
	if (size_b != 0)
		return (ft_printf("KO\n"), free(a), a = 0, free(b), b = 0, 0);
	while (i < size_a - 1 && a[i] < a[i + 1])
			i++;
	if (i == size_a - 1)
		return (ft_printf("OK\n"), free(a), a = 0, free(b), b = 0, 0);
	return (ft_printf("KO\n"), free(a), a = 0, free(b), b = 0, 0);
}
