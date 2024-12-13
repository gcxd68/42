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

static void	ft_bubble_sort(int *arr, size_t size)
{
	size_t	i;
	size_t	j;
	int		temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_map_values(int *stack, int *copy, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (stack[i] == copy[j])
			{
				stack[i] = j;
				j = size;
			}
			j++;
		}
		i++;
	}
}

int	*ft_simplify_arr(int *stack, size_t size)
{
	int		*copy;

	copy = ft_calloc(size, sizeof(int));
	if (!copy)
		ft_cleanup(NULL, 'e');
	ft_memcpy(copy, stack, size * sizeof(int));
	ft_bubble_sort(copy, size);
	ft_map_values(stack, copy, size);
	return (free(copy), copy = 0, stack);
}

void	ft_sort_few(int **stack, size_t size)
{
	if (size == 2)
		ft_printf("sa\n");
	else if (size == 3)
	{
		if (stack[0][1] > stack[0][0] && stack[0][1] > stack[0][2])
			ft_printf("rra\n");
		else if (stack[0][0] > stack[0][1] && stack[0][0] > stack[0][2])
			ft_printf("ra\n");
		if (stack[0][0] == 0 || (stack[0][0] == 1 && stack[0][1] == 0)
			|| (stack[0][0] == 2 && stack[0][1] == 1))
			ft_printf("sa\n");
	}
	if (size < 4)
		ft_cleanup(stack, 'n');
}

void	ft_radix_sort(int **stack, size_t *size, size_t max_size)
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
