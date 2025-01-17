/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:11:48 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/17 13:11:50 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_cleanup(int **arr, char msg)
{
	int	status;

	status = 0;
	if (msg == 'e')
	{
		ft_printf("Error\n");
		status = -1;
	}
	if (msg == 'o')
		ft_printf("OK\n");
	if (msg == 'k')
		ft_printf("KO\n");
	if (arr && arr[0])
	{
		free(arr[0]);
		arr[0] = 0;
	}
	if (arr && arr[1])
	{
		free(arr[1]);
		arr[1] = 0;
	}
	exit(status);
}

static void	ft_r_is_cheaper(int **stack, size_t *size, t_cost best_cost)
{
	size_t	i;

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

static void	ft_rr_is_cheaper(int **stack, size_t *size, t_cost best_cost)
{
	size_t	i;

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

static void	ft_m_is_cheaper(int **stack, size_t *size, t_cost best_cost)
{
	size_t	i;

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

void	ft_apply_strategy(int **stack, size_t *size, t_cost best_cost)
{
	if (best_cost.rot == 'r')
		ft_r_is_cheaper(stack, size, best_cost);
	if (best_cost.rot == '2')
		ft_rr_is_cheaper(stack, size, best_cost);
	if (best_cost.rot == 'm')
		ft_m_is_cheaper(stack, size, best_cost);
	ft_px(stack, size, 0, 1);
}
