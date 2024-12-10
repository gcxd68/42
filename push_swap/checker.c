/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:27 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/05 12:55:29 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

size_t static	ft_find_size(int argc, char **argv)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (argc < 2)
		return (1);
	i = 0;
	j = 0;
	while (i < (size_t)(argc - 1))
	{
		str = argv[i + 1];
		while (*str)
		{
			while (*str == ' ')
				str++;
			if (*str)
				j++;
			while (*str && *str != ' ')
				str++;
		}
		i++;
	}
	return (j);
}

void static	ft_dupcheck(int *a, size_t size_a)
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
			if (a[i] == a[j])
				ft_cleanup(a, NULL, 'e');
			j++;
		}
		i++;
	}
}

void static	ft_check_arr(int *a, int *b, size_t *size)
{
	size_t	i;

	i = 0;
	while (i < size[0] - 1 && a[i] < a[i + 1])
		i++;
	if (i == size[0] - 1 && size[1] == 0)
		ft_cleanup(a, b, 'o');
	ft_cleanup(a, b, 'k');
}

int	main(int argc, char *argv[])
{
	int		*a;
	int		*b;
	size_t	size[2];

	size[0] = ft_find_size(argc, argv);
	a = ft_calloc(size[0], sizeof(int));
	if (!a)
		ft_cleanup(NULL, NULL, 'e');
	ft_fill_arr(argc, argv, a);
	ft_dupcheck(a, size[0]);
	b = ft_calloc(size[0], sizeof(int));
	if (!b)
		ft_cleanup(a, NULL, 'e');
	size[1] = 0;
	ft_exec_ops(a, b, size);
	ft_check_arr(a, b, size);
	return (0);
}
