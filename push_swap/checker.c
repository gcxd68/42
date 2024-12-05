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

void	ft_sx(long long *arr)
{
	long long	tmp;

	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}

void	ft_px(long long *arr1, long long *arr2, long long *size_a1, long long *size_a2)
{
	long long	i;

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

void	ft_rx(long long *arr, long long *size)
{
	long long	tmp;
	long long	i;

	tmp = arr[0];
	i = 0;
	while (i < *size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = tmp;
}

void	ft_rrx(long long *arr, long long *size)
{
	long long	tmp;
	long long	i;

	i = *size - 1;
	tmp = arr[i];
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = tmp;
}

void	ft_stdin(long long *a, long long *b, long long *size_a, long long *size_b)
{
	char	*line;

	while ((line = get_next_line(0)))
	{
		if (ft_strncmp(line, "sa\n", 3) == 0 || ft_strncmp(line, "ss\n", 3) == 0)
			ft_sx(a);
		else if (ft_strncmp(line, "sb\n", 3) == 0 || ft_strncmp(line, "ss\n", 3) == 0)
			ft_sx(b);
		else if (ft_strncmp(line, "pa\n", 3) == 0)
			ft_px(a, b, size_a, size_b);
		else if (ft_strncmp(line, "pb\n", 3) == 0)
			ft_px(b, a, size_b, size_a);
		else if (ft_strncmp(line, "ra\n", 3) == 0 || ft_strncmp(line, "rr\n", 3) == 0)
			ft_rx(a, size_a);
		else if (ft_strncmp(line, "rb\n", 3) == 0 || ft_strncmp(line, "rr\n", 3) == 0)
			ft_rx(b, size_b);
		else if (ft_strncmp(line, "rra\n", 4) == 0 || ft_strncmp(line, "rrr\n", 4) == 0)
			ft_rrx(a, size_a);
		else if (ft_strncmp(line, "rrb\n", 4) == 0 || ft_strncmp(line, "rrr\n", 4) == 0)
			ft_rrx(b, size_b);
		free(line);
	}
}

int	main(int argc, char *argv[])
{
	long long	*a;
	long long	*b;
	long long 	size_a;
	long long	size_b;
	long long	i;

	size_a = argc - 1;
	size_b = 0;
	if (argc < 2)
		return (-1);
	a = ft_calloc(size_a + size_b, sizeof(long long));
	b = ft_calloc(size_a + size_b, sizeof(long long));
	if (!a || !b)
		return (1);
	i = 0;
	while (i < size_a)
	{
		a[i] = ft_atoi(argv[i + 1]);
		i++;
	}

	ft_stdin(a, b, &size_a, &size_b);

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

	free(a);
	a = NULL;
	free(b);
	b = NULL;
	return (0);
}
