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

static void   ft_bubble_sort(int *arr, size_t size)
{
    size_t  i;
    size_t  j;
    int     temp;

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

static int  *ft_simplify_arr(int *stack, size_t size)
{
    int     *copy;
    size_t  i;
    size_t  j;

    copy = ft_calloc(size, sizeof(int));
    if (!copy)
        ft_cleanup(NULL, 'e');
    ft_memcpy(copy, stack, size * sizeof(int));
    ft_bubble_sort(copy, size);
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
    return (free(copy), copy = 0, stack);
}

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

void	ft_find_min_max(int *stack, size_t size, int *min, int *max)
{
	size_t	i;

	if (size == 0 || !stack)
		return ;
	if (min)
		*min = INT_MAX;
	if (max)
		*max = INT_MIN;
	i = 0;
	while (i < size)
	{
		if (min && stack[i] < *min)
			*min = stack[i];
		if (max && stack[i] > *max)
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
	stack[0] = ft_simplify_arr(stack[0], size[0]);
	ft_sort_array(stack, size);
	return (0);
}
