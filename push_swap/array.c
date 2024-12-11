/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:20:55 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/10 13:20:56 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	ft_cleanup(int **arr, char msg)
{
	int	status;

	status = 0;
	if (msg == 'e')
	{
		ft_printf("Error\n");
		status = 1;
	}
	if (msg == 'o')
		ft_printf("OK\n");
	if (msg == 'k')
		ft_printf("KO\n");
	if (arr[0])
	{
		free(arr[0]);
		arr[0] = 0;
	}
	if (arr[1])
	{
		free(arr[1]);
		arr[1] = 0;
	}
	exit(status);
}

static int	ft_atoi_ps(const char *nptr, int **stack)
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
			ft_cleanup(stack, 'e');
		nptr++;
	}
	if (ft_isdigit(*nptr) == 0 && *nptr != '\0')
		ft_cleanup(stack, 'e');
	return ((int)res * sign);
}

void	ft_fill_arr(int argc, char **argv, int **stack)
{
	char	**split_res;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	while (i < (size_t)(argc - 1))
	{
		split_res = ft_split(argv[i + 1], ' ');
		if (!split_res)
			ft_cleanup(stack, 'e');
		k = 0;
		while (split_res[k])
		{
			stack[0][i + j] = ft_atoi_ps(split_res[k], stack);
			free(split_res[k]);
			k++;
			if (split_res[k])
				j++;
		}
		free(split_res);
		i++;
	}
}
