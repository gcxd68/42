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

void	ft_process_split(char **split_res, int *a, size_t *i, size_t *j)
{
	size_t	k;

	k = 0;
	while (split_res[k])
	{
		a[*i + *j - 1] = ft_atoi_psc(split_res[k], a);
		free(split_res[k]);
		k++;
		if (split_res[k])
			(*j)++;
	}
}

void	ft_fill_arr(int argc, char **argv, int *a)
{
	char	**split_res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (++i < (size_t)argc)
	{
		if (ft_strchr(argv[i], ' '))
		{
			split_res = ft_split(argv[i], ' ');
			if (!split_res)
				ft_cleanup(a, NULL, 'e');
			ft_process_split(split_res, a, &i, &j);
			free(split_res);
		}
		else
			a[i + j - 1] = ft_atoi_psc(argv[i], a);
	}
}

void	ft_exec_a_op(char *line, int *a, size_t *size_a)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		ft_sx(a, size_a);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		ft_rx(a, size_a);
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		ft_rrx(a, size_a);
}

void	ft_exec_b_op(char *line, int *b, size_t *size_b)
{
	if (ft_strncmp(line, "sb\n", 3) == 0)
		ft_sx(b, size_b);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		ft_rx(b, size_b);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		ft_rrx(b, size_b);
}

void	ft_handle_ops(int *a, int *b, size_t *size_a, size_t *size_b)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, "sa\n", 3) == 0 || ft_strncmp(line, "ra\n", 3) == 0
			|| ft_strncmp(line, "rra\n", 4) == 0)
			ft_exec_a_op(line, a, size_a);
		else if(ft_strncmp(line, "sb\n", 3) == 0 || ft_strncmp(line, "rb\n", 3) == 0
			|| ft_strncmp(line, "rrb\n", 4) == 0)
			ft_exec_b_op(line, b, size_b);
		else if (ft_strncmp(line, "ss\n", 3) == 0)
			ft_ss(a, b, size_a, size_b);
		else if (ft_strncmp(line, "pa\n", 3) == 0)
			ft_px(a, b, size_a, size_b);
		else if (ft_strncmp(line, "pb\n", 3) == 0)
			ft_px(b, a, size_b, size_a);
		else if (ft_strncmp(line, "rr\n", 3) == 0)
			ft_rr(a, b, size_a, size_b);
		else if (ft_strncmp(line, "rrr\n", 4) == 0)
			ft_rrr(a, b, size_a, size_b);
		else
			ft_cleanup(a, b, 'e');
		free(line);
		line = get_next_line(0);
	}
}

void	ft_dupcheck(int *a, size_t size_a)
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

void	ft_check_arr(int *a, int *b, size_t *size_a, size_t *size_b)
{
	size_t	i;

	i = 0;
	while (i < *size_a - 1 && a[i] < a[i + 1])
		i++;
	if (i == *size_a - 1 && *size_b == 0)
		ft_cleanup(a, b, 'o');
	ft_cleanup(a, b, 'k');
}

int	main(int argc, char *argv[])
{
	int		*a;
	int		*b;
	size_t	size_a;
	size_t	size_b;

	size_a = ft_find_size(argc, argv);
	a = ft_calloc(size_a, sizeof(int));
	if (!a)
		ft_cleanup(NULL, NULL, 'e');
	ft_fill_arr(argc, argv, a);
	ft_dupcheck(a, size_a);
	b = ft_calloc(size_a, sizeof(int));
	if (!b)
		ft_cleanup(a, NULL, 'e');
	ft_handle_ops(a, b, &size_a, &size_b);
	ft_check_arr(a, b, &size_a, &size_b);
	return (0);
}
