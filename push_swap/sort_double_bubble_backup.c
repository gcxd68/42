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

static void	ft_find_min_max(int *stack, size_t size, int *min, int *max)
{
	size_t	i;

	*min = size;
	*max = 0;
	i = 0;
	while (i < size && *min > 0 && *max < (int)size - 1)
	{
		if (stack[i] < *min)
			*min = stack[i];
		if (stack[i] > *max)
			*max = stack[i];
		i++;
	}
}

void	ft_sort_array(int **stack, size_t *size)
{
	int		min[2];
	int		max[2];
	size_t	i;

	i = 0;
	while(size[0] > size[1] + 1)
	{
		ft_printf("size[0] = %u, size[1] = %u\n", size[0], size[1]);
		if (stack[0][0] < (int)((size[0] + size[1]) / 2))
			ft_px(stack, size, 1, 1);
		else
			ft_rx(stack[0], size[0], 0, 1);
		i++;
	}

	ft_find_min_max(stack[0], size[0], &min[0], &max[0]);
	ft_find_min_max(stack[1], size[1], &min[1], &max[1]);

	i = 0;
	while (i < size[0] - 1 || i < size[1] - 1)
	{

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

		if (stack[0][0] > stack[0][1] && stack[1][0] < stack[1][1]
			&& stack[0][0] != max[0] && stack[0][1] != min[0]
			&& stack[1][0] != min[1] && stack[1][1] != max[1])
		{
			ft_sx(stack[0], size[0], 0, 0);
			ft_sx(stack[1], size[1], 1, 0);
			ft_printf("ss\n");
			if (i > 0)
			{
				ft_rrx(stack[0], size[0], 0, 0);
				ft_rrx(stack[1], size[1], 1, 0);
				ft_printf("rrr\n");
				i--;
			}
			else
			{
				ft_rx(stack[0], size[0], 0, 0);
				ft_rx(stack[1], size[1], 1, 0);
				ft_printf("rr\n");
				i++;
			}
		}
		else
		{
			ft_rx(stack[0], size[0], 0, 0);
			ft_rx(stack[1], size[1], 1, 0);
			ft_printf("rr\n");
			i++;
		}
	}
	ft_printf("i = %i\n", i);
	ft_cleanup(stack, 'n');
}
