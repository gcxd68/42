/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:15 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/12 11:14:17 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_sort(int **stack, size_t *size)
{
	size_t	i;

	i = 0;
	while (i < size[0] - 1)
	{
		if (stack[0][i] > stack[0][i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	ft_find_min(int *stack, size_t *size)
{
	int		min;
	size_t	i;

	min = size[0] + size[1];
	i = 0;
	while (i < size[0] && min > 0)
	{
		if (stack[i] < min)
			min = stack[i];
		i++;
	}
	return (min);
}

void	ft_find_min_max(int *stack, size_t size, int *min, int *max)
{
	size_t	i;

	if (size == 0)
		return ;
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

int	main(int argc, char *argv[])
{
	int		*stack[2];
	size_t	size[2];

	if (argc < 2)
		return (0);
	size[0] = ft_find_size(argc, argv);
	stack[0] = ft_calloc(size[0], sizeof(int));
	if (!stack[0])
		ft_cleanup(NULL, 'e');
	stack[1] = ft_calloc(size[0], sizeof(int));
	if (!stack[1])
		ft_cleanup(stack, 'e');
	size[1] = 0;
	ft_fill_arr(argc, argv, stack, size);
	if (ft_check_sort(stack, size) == 1)
		ft_cleanup(stack, 'n');
	ft_sort_array(stack, size);
	return (0);
}
