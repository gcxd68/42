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

int	main(int argc, char *argv[])
{
	int		*stack;
	size_t	size;

	if (argc < 2)
		return (0);
	size = ft_find_size(argc, argv);
	stack = ft_calloc(size, sizeof(int));
	if (!stack)
		ft_cleanup(NULL, 'e');


//	ft_fill_arr(argc, argv, stack);
//	ft_dupcheck(stack, size[0]);

	return (0);
}