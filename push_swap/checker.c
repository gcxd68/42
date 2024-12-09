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

void	ft_cleanup(int *arr1, int *arr2, char msg)
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
	if (arr1)
	{
		free(arr1);
		arr1 = 0;
	}
	if (arr2)
	{
		free(arr2);
		arr2 = 0;
	}
	exit(status);
}

int	ft_atoi_psc(const char *nptr, int *arr)
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
			ft_cleanup(arr, NULL, 'e');
		nptr++;
	}
	if (ft_isdigit(*nptr) == 0 && *nptr != '\0')
		ft_cleanup(arr, NULL, 'e');
	return ((int)res * sign);
}

size_t	ft_find_size(int argc, char **argv)
{
	char	*strchr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (argc < 2)
		return (1);
	while (i < (size_t)(argc - 1))
	{
		strchr = ft_strchr(argv[i + 1], ' ');
		while (strchr)
		{
			while (strchr[0] == ' ')
				strchr++;
			strchr = ft_strchr(strchr + 1, ' ');
			j++;
		}
		i++;
	}
	return (i + j);
}

int	*ft_fill_arr(int argc, char **argv, size_t size_a)
{
	char	**split_res;
	int		*arr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	arr = ft_calloc(size_a, sizeof(int));
	if (!arr)
		ft_cleanup(NULL, NULL, 'e');
	while (i < (size_t)(argc - 1))
	{
		if (ft_strchr(argv[i + 1], ' '))
		{
			split_res = ft_split(argv[i + 1], ' ');
			if (!split_res)
				ft_cleanup(arr, NULL, 'e');
			j = 0;
			while (split_res[j])
			{
				arr[i + k] = ft_atoi_psc(split_res[j], arr);
				free(split_res[j]);
				j++;
				if (split_res[j])
					k++;
			}
			free(split_res);
		}
		else
			arr[i + k] = ft_atoi_psc(argv[i + 1], arr);
		i++;
	}
	return (arr);
}

size_t	ft_stdin(int *a, int *b, size_t *size_a)
{
	char	*line;
	size_t	size_b;

	size_b = 0;
	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, "sa\n", 3) == 0)
			ft_sx(a, size_a);
		else if (ft_strncmp(line, "sb\n", 3) == 0)
			ft_sx(b, &size_b);
		else if (ft_strncmp(line, "ss\n", 3) == 0)
		{
			ft_sx(a, size_a);
			ft_sx(b, &size_b);
		}
		else if (ft_strncmp(line, "pa\n", 3) == 0)
			ft_px(a, b, size_a, &size_b);
		else if (ft_strncmp(line, "pb\n", 3) == 0)
			ft_px(b, a, &size_b, size_a);
		else if (ft_strncmp(line, "ra\n", 3) == 0)
			ft_rx(a, size_a);
		else if (ft_strncmp(line, "rb\n", 3) == 0)
			ft_rx(b, &size_b);
		else if (ft_strncmp(line, "rr\n", 3) == 0)
		{
			ft_rx(a, size_a);
			ft_rx(b, &size_b);
		}
		else if (ft_strncmp(line, "rra\n", 4) == 0)
			ft_rrx(a, size_a);
		else if (ft_strncmp(line, "rrb\n", 4) == 0)
			ft_rrx(b, &size_b);
		else if (ft_strncmp(line, "rrr\n", 4) == 0)
		{
			ft_rrx(a, size_a);
			ft_rrx(b, &size_b);
		}
		else
			ft_cleanup(a, b, 'e');
		free(line);
		line = get_next_line(0);
	}
	return (size_b);
}

void	ft_read_check(int *a, size_t *size_a)
{
	int		*b;
	size_t	size_b;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < *size_a - 1)
	{
		j = i + 1;
		while (j < *size_a)
		{
			if (a[i] == a[j])
				ft_cleanup(a, NULL, 'e');
			j++;
		}
		i++;
	}
	b = ft_calloc(*size_a, sizeof(int));
	if (!b)
		ft_cleanup(a, NULL, 'e');
	size_b = ft_stdin(a, b, size_a);
	i = 0;
	while (i < *size_a - 1 && a[i] < a[i + 1])
		i++;
	if (i == *size_a - 1 && size_b == 0)
		ft_cleanup(a, b, 'o');
	ft_cleanup(a, b, 'k');
}

int	main(int argc, char *argv[])
{
	int		*a;
	size_t	size_a;

	size_a = ft_find_size(argc, argv);
	a = ft_fill_arr(argc, argv, size_a);
	ft_read_check(a, &size_a);
	return (0);
}
