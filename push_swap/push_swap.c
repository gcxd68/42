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

static size_t	ft_find_size(int argc, char **argv)
{
	char	*str;
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (i < (size_t)(argc - 1))
	{
		str = argv[i + 1];
		while (*str)
		{
			while (*str == ' ')
				str++;
			if (*str)
				size++;
			while (*str && *str != ' ')
				str++;
		}
		i++;
	}
	return (size);
}

static void	ft_dupcheck(int **stack, size_t size_a)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < size_a - 1)
	{
		j = i + 1;
		while (j < size_a)
		{
			if (stack[0][i] == stack[0][j])
				ft_cleanup(stack, 'e');
			j++;
		}
		i++;
	}
}

void	ft_check_arr(int **stack, size_t *size)
{
	size_t	i;

	if (!stack || !stack[0])
		ft_cleanup(stack, 'e');
	i = 0;
	while (i < size[0] - 1 && stack[0][i] < stack[0][i + 1])
		i++;
	if (i == size[0] - 1 && size[1] == 0)
		ft_cleanup(stack, 'n');
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
	ft_fill_arr(argc, argv, stack);
	ft_dupcheck(stack, size[0]);
	ft_check_arr(stack, size);
	stack[0] = ft_simplify_arr(stack[0], size[0]);
	ft_sort_array(stack, size);
	return (0);
}
