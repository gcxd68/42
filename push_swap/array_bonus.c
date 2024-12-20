/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:20:55 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/10 13:20:56 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	ft_free_split_ret(int **stack, char **split_ret, size_t *k)
{
	while (split_ret[*k])
	{
		free(split_ret[*k]);
		(*k)++;
	}
	free(split_ret);
	ft_cleanup(stack, 'e');
}

static int	ft_atoi_ps(char *nptr, int **stack, char **split_ret, size_t *k)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + *nptr - '0';
		if ((sign == 1 && res > (unsigned)INT_MAX)
			|| (sign == -1 && res > (unsigned)(-(long)INT_MIN)))
			ft_free_split_ret(stack, split_ret, k);
		nptr++;
	}
	if ((*nptr < '0' || *nptr > '9') && *nptr != '\0')
		ft_free_split_ret(stack, split_ret, k);
	return ((int)res * sign);
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

void	ft_fill_arr(int argc, char **argv, int **stack, size_t *size)
{
	char	**split_ret;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < (size_t)(argc - 1))
	{
		split_ret = ft_split(argv[i + 1], ' ');
		if (!split_ret)
			ft_cleanup(stack, 'e');
		k = 0;
		while (split_ret[k])
		{
			stack[0][i + j] = ft_atoi_ps(split_ret[k], stack, split_ret, &k);
			free(split_ret[k]);
			k++;
			if (split_ret[k])
				j++;
		}
		free(split_ret);
		i++;
	}
	ft_dupcheck(stack, size[0]);
}

size_t	ft_find_size(int argc, char **argv)
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
