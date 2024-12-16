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

static void	ft_find_min_max(int *stack, size_t size, int *min, int *max)
{
	size_t	i;

	if (size == 0)
		return;
	*min = stack[0];
	*max = stack[0];
	i = 1;
	while (i < size)
	{
		if (stack[i] < *min)
			*min = stack[i];
		if (stack[i] > *max)
			*max = stack[i];
		i++;
	}
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

		size_t	idx;
		ft_printf("\n");
		ft_printf("Contenu de la pile A :\n");
		for (idx = 0; idx < size[0]; idx++)
			ft_printf("%d ", stack[0][idx]);
		ft_printf("\n\n");
		ft_printf("Contenu de la pile B :\n");
		for (idx = 0; idx < size[1]; idx++)
			ft_printf("%d ", stack[1][idx]);
		ft_printf("\n\n");

	while (size[1] > 0)
	{
		best_cost.total = INT_MAX;
		j = 0;
		ft_find_min_max(stack[0], size[0], &min_a, &max_a);
		ft_printf("min_a = %i, max_a = %i\n", min_a, max_a);
		while (j < size[1])
		{
			top_b = stack[1][j];
			i = 0;
			curr_a = stack[0][i];
			prev_a = stack[0][size[0] - 1];
			while (i < size[0])
			{
				if (top_b > max_a)
				{
					while (stack[0][i] != min_a)
                    	i++;
                	break;
				}
				if (top_b < min_a)
				{
            	    while (stack[0][i] != min_a)
                	    i++;
                	break;
				}
				if (top_b > prev_a && top_b < curr_a)
					break;
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
			if (cost.ra + cost.rrb < cost.total || cost.rra + cost.rb < cost.total)
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
			ft_printf("Cout de transfert de stack[1][%u]=%i au-dessus de stack[0][%u]=%i : RA=%i, RRA=%i, RB=%i, RRB=%i, PA=1, TOTAL=%i\n",
				j, top_b, i, curr_a, cost.ra, cost.rra, cost.rb, cost.rrb, cost.total);
			j++;
		}
		ft_printf("\n");
		ft_printf("Meilleur cout : transfert de stack[1][%u]=%i au-dessus de stack[0][%u]=%i : RA=%i, RRA=%i, RB=%i, RRB=%i, PA=1, TOTAL=%i\n",
				best_cost.rb, stack[1][best_cost.rb], best_cost.ra, stack[0][best_cost.ra], best_cost.ra, best_cost.rra, best_cost.rb, best_cost.rrb, best_cost.total);

		ft_printf("\n");

		if (best_cost.rot == 'r')
		{
			if (best_cost.ra < best_cost.rb)
				ft_printf("Stategie a appliquer : %i RA, %i RB, %i RR, 1 PA\n", 0, best_cost.rb - best_cost.ra, best_cost.ra);
			else
				ft_printf("Stategie a appliquer : %i RA, %i RB, %i RR, 1 PA\n", best_cost.ra - best_cost.rb, 0, best_cost.rb);
		}	
		if (best_cost.rot == '2')
		{
			if (best_cost.rra < best_cost.rrb)
				ft_printf("Stategie a appliquer : %i RRA, %i RRB, %i RRR, 1 PA\n", 0, best_cost.rrb - best_cost.rra, best_cost.rra);
			else
				ft_printf("Stategie a appliquer : %i RRA, %i RRB, %i RRR, 1 PA\n", best_cost.rra - best_cost.rrb, 0, best_cost.rrb);
		}
		if (best_cost.rot == 'm')
		{
			if (best_cost.ra + best_cost.rrb < best_cost.rra + best_cost.rb)
				ft_printf("Stategie a appliquer : %i RA, %i RRB, 1 PA\n", best_cost.ra, best_cost.rrb);
			else
				ft_printf("Stategie a appliquer : %i RRA, %i RB, 1 PA\n", best_cost.rra, best_cost.rb);
		}

		if (best_cost.rot == 'r')
		{
			if (best_cost.ra < best_cost.rb)
			{
				i = 0;
				while (i < best_cost.rb - best_cost.ra)
				{
					ft_rx(stack[1], size[1], 1, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.ra)
				{
					ft_rx(stack[0], size[0], 0, 0);
					ft_rx(stack[1], size[1], 1, 0);
					ft_printf("rr\n");
					i++;
				}
			}
			else
			{
				i = 0;
				while (i < best_cost.ra - best_cost.rb)
				{
					ft_rx(stack[0], size[0], 0, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.rb)
				{
					ft_rx(stack[0], size[0], 0, 0);
					ft_rx(stack[1], size[1], 1, 0);
					ft_printf("rr\n");
					i++;
				}
			}
		}	
		if (best_cost.rot == '2')
		{
			if (best_cost.rra < best_cost.rrb)
			{
				i = 0;
				while (i < best_cost.rrb - best_cost.rra)
				{
					ft_rrx(stack[1], size[1], 1, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.rra)
				{
					ft_rrx(stack[0], size[0], 0, 1);
					ft_rrx(stack[1], size[1], 1, 1);
					ft_printf("rrr\n");
					i++;
				}
			}
			else
			{
				i = 0;
				while (i < best_cost.rra - best_cost.rrb)
				{
					ft_rrx(stack[0], size[0], 0, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.rrb)
				{
					ft_rrx(stack[0], size[0], 0, 1);
					ft_rrx(stack[1], size[1], 1, 1);
					ft_printf("rrr\n");
					i++;
				}
			}
		}
		if (best_cost.rot == 'm')
		{
			if (best_cost.ra + best_cost.rrb < best_cost.rra + best_cost.rb)
			{
				i = 0;
				while (i < best_cost.ra)
				{
					ft_rx(stack[0], size[0], 0, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.rrb)
				{
					ft_rrx(stack[1], size[1], 1, 1);
					i++;
				}
			}
			else
			{
				i = 0;
				while (i < best_cost.rra)
				{
					ft_rrx(stack[0], size[0], 0, 1);
					i++;
				}
				i = 0;
				while (i < best_cost.rb)
				{
					ft_rx(stack[1], size[1], 1, 1);
					i++;
				}
			}
		}
		ft_px(stack, size, 0, 1);

		size_t	idx;
		ft_printf("\n");
		ft_printf("Contenu de la pile A :\n");
		for (idx = 0; idx < size[0]; idx++)
			ft_printf("%d ", stack[0][idx]);
		ft_printf("\n\n");
		ft_printf("Contenu de la pile B :\n");
		for (idx = 0; idx < size[1]; idx++)
			ft_printf("%d ", stack[1][idx]);
		ft_printf("\n\n");
	}
	i = 0;
	while (stack[0][i] != min_a)
		i++;
	if (i < (size[0] + 1) / 2)
		while (stack[0][0] != min_a)
			ft_rx(stack[0], size[0], 0, 1);
	else
	{
		while (stack[0][0] != min_a)
			ft_rrx(stack[0], size[0], 0, 1);
	}

		ft_printf("\n");
		ft_printf("Contenu de la pile A :\n");
		for (idx = 0; idx < size[0]; idx++)
			ft_printf("%d ", stack[0][idx]);
		ft_printf("\n\n");
		ft_printf("Contenu de la pile B :\n");
		for (idx = 0; idx < size[1]; idx++)
			ft_printf("%d ", stack[1][idx]);
		ft_printf("\n\n");
}

void	ft_sort_array(int **stack, size_t *size)
{
	if (size[0] < 4)
		ft_sort_few(stack[0], size[0]);
	else if (size[0] == 4)
		ft_sort_four(stack, size);
	else if (size[0] == 5)
		ft_sort_five(stack, size);
	else
		ft_sort_many(stack, size);
	ft_cleanup(stack, 'n');
}
