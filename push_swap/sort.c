/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:03:29 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/12 17:03:32 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_sort_few(int **stack, size_t *size)
{
	if (size[0] == 2)
		ft_printf("sa\n");
	else if (size[0] == 3)
	{
		if (stack[0][1] > stack[0][0] && stack[0][1] > stack[0][2])
			ft_rrx(stack[0], size[0], 'a', 1);
		else if (stack[0][0] > stack[0][1] && stack[0][0] > stack[0][2])
			ft_rx(stack[0], size[0], 'a', 1);
		if (stack[0][0] > stack[0][1] || stack[0][1] > stack[0][2])
			ft_sx(stack[0], size[0], 'a', 1);
	}
	ft_check_arr(stack, size);
}

static void	ft_sort_four(int **stack, size_t *size)
{
	int		min;
	size_t	i;

	i = 0;
	min = 0;
	while (i++ < size[0])
	{
		if (stack[0][i] == 4)
		{
			min = 1;
			break ;
		}
	}
	while (stack[0][0] != min && stack[0][size[0] - 1] != min)
		ft_rx(stack[0], size[0], 'a', 1);
	if (stack[0][size[0] - 1] == min)
		ft_rrx(stack[0], size[0], 'a', 1);
	ft_check_arr(stack, size);
	ft_px(stack, size, 'b', 1);
	ft_sort_few(stack, size);
	ft_px(stack, size, 'a', 1);
	ft_check_arr(stack, size);
}

static void	ft_sort_five(int **stack, size_t *size)
{
	while (stack[0][0] != 0 && stack[0][size[0] - 1] != 0 && stack[0][size[0] - 2] != 0)
		ft_rx(stack[0], size[0], 'a', 1);
	if (stack[0][size[0] - 1] == 0)
		ft_rrx(stack[0], size[0], 'a', 1);
	else if (stack[0][size[0] - 2] == 0)
	{
		ft_rrx(stack[0], size[0], 'a', 1);
		ft_rrx(stack[0], size[0], 'a', 1);
	}
	ft_check_arr(stack, size);
	ft_px(stack, size, 'b', 1);
	ft_sort_four(stack, size);
	ft_px(stack, size, 'a', 1);
	ft_check_arr(stack, size);
}

static void	ft_sort_many(int **stack, size_t *size, size_t max_size)
{
	size_t	max_bits;
	size_t	i;
	size_t	j;

	max_bits = 0;
	while (((max_size - 1) >> max_bits) != 0)
		max_bits++;
	i = 0;
	while (i < max_bits)
	{
		j = 0;
		while (j < max_size)
		{
			if (((stack[0][0] >> i) & 1) == 1)
				ft_rx(stack[0], size[0], 'a', 1);
			else
				ft_px(stack, size, 'b', 1);
			j++;
		}
		while (size[1] > 0)
			ft_px(stack, size, 'a', 1);
		i++;
	}
	ft_cleanup(stack, 'n');
}

void	ft_sort_array(int **stack, size_t *size)
{
	if (size[0] < 4)
		ft_sort_few(stack, size);
	else if (size[0] == 4)
		ft_sort_four(stack, size);
	else if (size[0] == 5)
		ft_sort_five(stack, size);
	else
		ft_sort_many(stack, size, size[0]);
}
