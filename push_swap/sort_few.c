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
	if (size[0] == 2 && stack[0][0] > stack[0][1])
		ft_sx(stack, size, 0, 1);
	else if (size[0] == 3)
	{
		if (stack[0][1] > stack[0][0] && stack[0][1] > stack[0][2])
			ft_rrx(stack, size, 0, 1);
		else if (stack[0][0] > stack[0][1] && stack[0][0] > stack[0][2])
			ft_rx(stack, size, 0, 1);
		if (stack[0][0] > stack[0][1] || stack[0][1] > stack[0][2])
			ft_sx(stack, size, 0, 1);
	}
}

static void	ft_sort_four(int **stack, size_t *size)
{
	int	bound[2];

	ft_find_bounds(stack[0], size[0], bound);
	while (stack[0][0] != bound[0] && stack[0][size[0] - 1] != bound[0])
		ft_rx(stack, size, 0, 1);
	if (stack[0][size[0] - 1] == bound[0])
		ft_rrx(stack, size, 0, 1);
	if (ft_check_sort(stack, size) == 1)
		return ;
	ft_px(stack, size, 1, 1);
	ft_sort_few(stack, size);
	ft_px(stack, size, 0, 1);
}

void	ft_sort_five(int **stack, size_t *size)
{
	int	bound[2];

	ft_find_bounds(stack[0], size[0], bound);
	while (stack[0][0] != bound[0] && stack[0][size[0] - 1] != bound[0]
		&& stack[0][size[0] - 2] != bound[0])
		ft_rx(stack, size, 0, 1);
	if (stack[0][size[0] - 1] == bound[0])
		ft_rrx(stack, size, 0, 1);
	else if (stack[0][size[0] - 2] == bound[0])
	{
		ft_rrx(stack, size, 0, 1);
		ft_rrx(stack, size, 0, 1);
	}
	if (ft_check_sort(stack, size) == 1)
		return ;
	ft_px(stack, size, 1, 1);
	ft_sort_four(stack, size);
	ft_px(stack, size, 0, 1);
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
		ft_sort_many(stack, size);
	ft_cleanup(stack, 'n');
}
