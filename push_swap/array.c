/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <gdosch@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:20:55 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/19 15:50:25 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_free_split_ret(char **split_ret)
{
	size_t	i;

	i = 0;
	while (split_ret[i])
	{
		free(split_ret[i]);
		split_ret[i] = 0;
		i++;
	}
	free(split_ret);
	split_ret = 0;
}

static int	ft_atoi_ps(char **split_ret, ssize_t *k)
{
	unsigned long long	res;
	int					sign;
	char				*ptr;

	sign = 1;
	res = 0;
	ptr = split_ret[*k];
	while ((*ptr >= '\t' && *ptr <= '\r') || *ptr == ' ')
		ptr++;
	if (*ptr == '-')
		sign = -1;
	if (*ptr == '-' || *ptr == '+')
		ptr++;
	while (*ptr >= '0' && *ptr <= '9')
	{
		res = res * 10 + *ptr - '0';
		if ((sign == 1 && res > (unsigned)INT_MAX)
			|| (sign == -1 && res > (unsigned)(-(long)INT_MIN)))
			return (ft_free_split_ret(split_ret), *k = -1, 0);
		ptr++;
	}
	if ((*ptr < '0' || *ptr > '9') && *ptr != '\0')
		return (ft_free_split_ret(split_ret), *k = -1, 0);
	return ((int)res * sign);
}

void	ft_dupcheck(int **stack, size_t size_a)
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

void	ft_fill_arr(int argc, char **argv, int **stack)
{
	char	**split_ret;
	size_t	i;
	size_t	j;
	ssize_t	k;

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
			stack[0][i + j] = ft_atoi_ps(split_ret, &k);
			if (k < 0)
				ft_cleanup(stack, 'e');
			k++;
			if (split_ret[k])
				j++;
		}
		ft_free_split_ret(split_ret);
		i++;
	}
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
