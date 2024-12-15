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

static void	ft_sort_few(int *stack, size_t size)
{
	if (size == 2 && stack[0] > stack[1])
		ft_sx(stack, size, 0, 1);
	else if (size == 3)
	{
		if (stack[1] > stack[0] && stack[1] > stack[2])
			ft_rrx(stack, size, 0, 1);
		else if (stack[0] > stack[1] && stack[0] > stack[2])
			ft_rx(stack, size, 0, 1);
		if (stack[0] > stack[1] || stack[1] > stack[2])
			ft_sx(stack, size, 0, 1);
	}
}

static void	ft_sort_four(int **stack, size_t *size)
{
	int	min;

	min = ft_find_min(stack[0], size);
	while (stack[0][0] != min && stack[0][size[0] - 1] != min)
		ft_rx(stack[0], size[0], 0, 1);
	if (stack[0][size[0] - 1] == min)
		ft_rrx(stack[0], size[0], 0, 1);
	if (ft_check_sort(stack, size) == 1)
		return ;
	ft_px(stack, size, 1, 1);
	ft_sort_few(stack[0], size[0]);
	ft_px(stack, size, 0, 1);
}

static void	ft_sort_five(int **stack, size_t *size)
{
	int	min;

	min = ft_find_min(stack[0], size);
	while (stack[0][0] != min && stack[0][size[0] - 1] != min
		&& stack[0][size[0] - 2] != min)
		ft_rx(stack[0], size[0], 0, 1);
	if (stack[0][size[0] - 1] == min)
		ft_rrx(stack[0], size[0], 0, 1);
	else if (stack[0][size[0] - 2] == min)
	{
		ft_rrx(stack[0], size[0], 0, 1);
		ft_rrx(stack[0], size[0], 0, 1);
	}
	if (ft_check_sort(stack, size) == 1)
		return ;
	ft_px(stack, size, 1, 1);
	ft_sort_four(stack, size);
	ft_px(stack, size, 0, 1);
}

static void	ft_sort_many(int **stack, size_t *size, size_t max_bits)
{
	size_t	i;
	size_t	j;
	int		use_stack_a;

	i = 0;
	while (i < max_bits)
	{
		use_stack_a = size[0];
		j = 0;
		while (j < size[0] + size[1])
		{
			if (use_stack_a > 0 && ((stack[0][0] >> i) & 1) == 1)
				ft_rx(stack[0], size[0], 0, 1);
			else if (use_stack_a == 0 && ((stack[1][0] >> i) & 1) == 0)
				ft_rx(stack[1], size[1], 1, 1);
			else
				ft_px(stack, size, (use_stack_a > 0), 1);
			j++;
		}
		while (size[(size[0] >= size[1] || i == max_bits - 1)] > 0)
			ft_px(stack, size, (size[0] < size[1] && i != max_bits - 1), 1);
		i++;
	}
}

void	ft_sort_array(int **stack, size_t *size)
{
	size_t	max_bits;

	if (size[0] < 4)
		ft_sort_few(stack[0], size[0]);
	else if (size[0] == 4)
		ft_sort_four(stack, size);
	else if (size[0] == 5)
		ft_sort_five(stack, size);
	else
	{
		max_bits = 0;
		while (((size[0] + size[1] - 1) >> max_bits) != 0)
			max_bits++;
		ft_sort_many(stack, size, max_bits);
	}
	ft_cleanup(stack, 'n');
}
