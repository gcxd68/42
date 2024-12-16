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
	int	min;

	min = ft_find_min(stack[0], size);
	while (stack[0][0] != min && stack[0][size[0] - 1] != min)
		ft_rx(stack, size, 0, 1);
	if (stack[0][size[0] - 1] == min)
		ft_rrx(stack, size, 0, 1);
	if (ft_check_sort(stack, size) == 1)
		return ;
	ft_px(stack, size, 1, 1);
	ft_sort_few(stack, size);
	ft_px(stack, size, 0, 1);
}

static void	ft_sort_five(int **stack, size_t *size)
{
	int	min;

	min = ft_find_min(stack[0], size);
	while (stack[0][0] != min && stack[0][size[0] - 1] != min
		&& stack[0][size[0] - 2] != min)
		ft_rx(stack, size, 0, 1);
	if (stack[0][size[0] - 1] == min)
		ft_rrx(stack, size, 0, 1);
	else if (stack[0][size[0] - 2] == min)
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

static void	ft_sort_many(int **stack, size_t *size)
{
	t_cost	best_cost;
	t_cost	cost;
	int		prev_a;
	int		curr_a;
	int		top_b;
	int		min_a;
	int		max_a;
	size_t	i;
	size_t	j;

	while (size[0] > 5)
		ft_px(stack, size, 1, 1);
	ft_sort_five(stack, size);
	while (size[1] > 0)
	{
		best_cost.total = INT_MAX;
		j = 0;
		ft_find_min_max(stack[0], size[0], &min_a, &max_a);
		while (j < size[1])
		{
			top_b = stack[1][j];
			i = 0;
			curr_a = stack[0][i];
			prev_a = stack[0][size[0] - 1];
			while (i < size[0])
			{
				if (top_b > max_a || top_b < min_a)
				{
					while (stack[0][i] != min_a)
						i++;
					break ;
				}
				if (top_b > prev_a && top_b < curr_a)
					break ;
				i++;
				if (i < size[0])
				{
					prev_a = stack[0][i - 1];
					curr_a = stack[0][i];
				}
			}
			cost.ra = i;
			cost.rra = size[0] - i;
			cost.rb = j;
			cost.rrb = size[1] - j;
			cost.rot = 'r';
			cost.total = cost.ra;
			if (cost.rb > cost.ra)
				cost.total = cost.rb;
			if (cost.rra < cost.total || cost.rrb < cost.total)
			{
				if (cost.rra > cost.rrb && cost.rra < cost.total)
					cost.total = cost.rra;
				else if (cost.rra < cost.rrb && cost.rrb < cost.total)
					cost.total = cost.rrb;
				cost.rot = '2';
			}
			if (cost.ra + cost.rrb < cost.total
				|| cost.rra + cost.rb < cost.total)
			{
				if (cost.ra + cost.rrb < cost.total)
					cost.total = cost.ra + cost.rrb;
				if (cost.rra + cost.rb < cost.total)
					cost.total = cost.rra + cost.rb;
				cost.rot = 'm';
			}
			cost.total++;
			if (best_cost.total > cost.total)
				best_cost = cost;
			j++;
		}
		if (best_cost.rot == 'r')
		{
			if (best_cost.ra < best_cost.rb)
			{
				i = 0;
				while (i++ < best_cost.rb - best_cost.ra)
					ft_rx(stack, size, 1, 1);
				i = 0;
				while (i++ < best_cost.ra)
					ft_rx(stack, size, 2, 1);
			}
			else
			{
				i = 0;
				while (i++ < best_cost.ra - best_cost.rb)
					ft_rx(stack, size, 0, 1);
				i = 0;
				while (i++ < best_cost.rb)
					ft_rx(stack, size, 2, 1);
			}
		}
		if (best_cost.rot == '2')
		{
			if (best_cost.rra < best_cost.rrb)
			{
				i = 0;
				while (i++ < best_cost.rrb - best_cost.rra)
					ft_rrx(stack, size, 1, 1);
				i = 0;
				while (i++ < best_cost.rra)
					ft_rrx(stack, size, 2, 1);
			}
			else
			{
				i = 0;
				while (i++ < best_cost.rra - best_cost.rrb)
					ft_rrx(stack, size, 0, 1);
				i = 0;
				while (i++ < best_cost.rrb)
					ft_rrx(stack, size, 2, 1);
			}
		}
		if (best_cost.rot == 'm')
		{
			if (best_cost.ra + best_cost.rrb < best_cost.rra + best_cost.rb)
			{
				i = 0;
				while (i++ < best_cost.ra)
					ft_rx(stack, size, 0, 1);
				i = 0;
				while (i++ < best_cost.rrb)
					ft_rrx(stack, size, 1, 1);
			}
			else
			{
				i = 0;
				while (i++ < best_cost.rra)
					ft_rrx(stack, size, 0, 1);
				i = 0;
				while (i++ < best_cost.rb)
					ft_rx(stack, size, 1, 1);
			}
		}
		ft_px(stack, size, 0, 1);
	}
	i = 0;
	while (stack[0][i] != min_a)
		i++;
	if (i < (size[0] + 1) / 2)
		while (stack[0][0] != min_a)
			ft_rx(stack, size, 0, 1);
	else
	{
		while (stack[0][0] != min_a)
			ft_rrx(stack, size, 0, 1);
	}
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
