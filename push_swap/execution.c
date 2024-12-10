/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:16:50 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/10 13:16:51 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void static	ft_exec_a_op(char *line, int *a, size_t *size_a)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		ft_sx(a, size_a);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		ft_rx(a, size_a);
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		ft_rrx(a, size_a);
}

void static	ft_exec_b_op(char *line, int *b, size_t *size_b)
{
	if (ft_strncmp(line, "sb\n", 3) == 0)
		ft_sx(b, size_b);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		ft_rx(b, size_b);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		ft_rrx(b, size_b);
}

void static	ft_exec_ab_op(char *line, int *a, int *b, size_t *size)
{
	if (ft_strncmp(line, "ss\n", 3) == 0)
	{
		ft_sx(a, &size[0]);
		ft_sx(b, &size[1]);
	}
	else if (ft_strncmp(line, "rr\n", 3) == 0)
	{
		ft_rx(a, &size[0]);
		ft_rx(b, &size[1]);
	}
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
	{
		ft_rrx(a, &size[0]);
		ft_rrx(b, &size[1]);
	}
}

void	ft_exec_ops(int *a, int *b, size_t *size)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, "sa\n", 3) == 0 || ft_strncmp(line, "ra\n", 3) == 0
			|| ft_strncmp(line, "rra\n", 4) == 0)
			ft_exec_a_op(line, a, &size[0]);
		else if (ft_strncmp(line, "sb\n", 3) == 0
			|| ft_strncmp(line, "rb\n", 3) == 0
			|| ft_strncmp(line, "rrb\n", 4) == 0)
			ft_exec_b_op(line, b, &size[1]);
		else if (ft_strncmp(line, "ss\n", 3) == 0
			|| ft_strncmp(line, "rr\n", 3) == 0
			|| ft_strncmp(line, "rrr\n", 4) == 0)
			ft_exec_ab_op(line, a, b, size);
		else if (ft_strncmp(line, "pa\n", 3) == 0)
			ft_px(a, b, &size[0], &size[1]);
		else if (ft_strncmp(line, "pb\n", 3) == 0)
			ft_px(b, a, &size[1], &size[0]);
		else
			ft_cleanup(a, b, 'e');
		free(line);
		line = get_next_line(0);
	}
}
