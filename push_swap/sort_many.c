/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_many.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:11:48 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/17 13:11:50 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_first_sort(int **stack, size_t *size)
{
	while (size[0] > ((size[0] + size[1]) / 2))
	{
		if (stack[0][0] < (int)((size[0] + size[1]) / 4))
		{
			ft_px(stack, size, 1, 1);
			ft_rx(stack, size, 1, 1);
		}
		else if (stack[0][0] >= (int)((size[0] + size[1]) * 3 / 4))
			ft_px(stack, size, 1, 1);
		else
			ft_rx(stack, size, 0, 1);
	}
	while (size[0] > 5)
	{
		if (stack[0][0] < (int)((size[0] + size[1]) / 2))
		{
			ft_px(stack, size, 1, 1);
			ft_rx(stack, size, 1, 1);
		}
		else if (stack[0][0] >= (int)((size[0] + size[1]) / 2))
			ft_px(stack, size, 1, 1);
	}
}

static void	ft_best_cost(t_cost cost, t_cost *best_cost)
{
	cost.rot = 'r';
	cost.total = cost.ra;
	if (cost.rb > cost.ra)
		cost.total = cost.rb;
	if (cost.rra < cost.total && cost.rrb < cost.total)
	{
		if (cost.rra >= cost.rrb && cost.rra < cost.total)
			cost.total = cost.rra;
		else if (cost.rra < cost.rrb && cost.rrb < cost.total)
			cost.total = cost.rrb;
		cost.rot = '2';
	}
	if (cost.ra + cost.rrb < cost.total || cost.rra + cost.rb < cost.total)
	{
		cost.total = cost.ra + cost.rrb;
		if (cost.rra + cost.rb < cost.total)
			cost.total = cost.rra + cost.rb;
		cost.rot = 'm';
	}
	cost.total++;
	if (best_cost->total > cost.total)
		*best_cost = cost;
}

static void	ft_get_costs(int **stack, size_t *size, int *bound, t_cost *best_cost)
{
	t_cost	cost;
	size_t	i;
	size_t	j;

	j = 0;
	while (j < size[1])
	{
		i = 0;
		while (i < size[0] && (!(i == 0 && stack[1][j] > stack[0][size[0] - 1]
			&& stack[1][j] < stack[0][i]) && !(i != 0 && stack[1][j]
			> stack[0][i - 1] && stack[1][j] < stack[0][i]) && !((stack[1][j]
			> bound[1] || stack[1][j] < bound[0]) && stack[0][i] == bound[0])))
			i++;
		cost.ra = i;
		cost.rra = size[0] - i;
		cost.rb = j;
		cost.rrb = size[1] - j;
		ft_best_cost(cost, best_cost);
		j++;
	}
}

static void	ft_last_sort(int **stack, size_t *size)
{
	int		bound[2];
	size_t	i;

	i = 0;
	ft_find_bounds(stack[0], size[0], bound);
	while (stack[0][i] != bound[0])
		i++;
	if (i < (size[0] + 1) / 2)
		while (stack[0][0] != bound[0])
			ft_rx(stack, size, 0, 1);
	else
	{
		while (stack[0][0] != bound[0])
			ft_rrx(stack, size, 0, 1);
	}
}

void	ft_sort_many(int **stack, size_t *size)
{
	t_cost	best_cost;
	int		bound[2];

	ft_first_sort(stack, size);
	ft_sort_five(stack, size);
	while (size[1] > 0)
	{
		best_cost.total = INT_MAX;
		ft_find_bounds(stack[0], size[0], bound);
		ft_get_costs(stack, size, bound, &best_cost);
		ft_apply_strategy(stack, size, best_cost);
	}
	ft_last_sort(stack, size);
}
