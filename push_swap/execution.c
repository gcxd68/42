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

static void	ft_exec_x_op(char *line, int **stack, size_t *size)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		ft_sx(stack[0], size[0], 'a', 0);
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		ft_sx(stack[1], size[1], 'b', 0);
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		ft_px(stack, size, 'a', 0);
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		ft_px(stack, size, 'b', 0);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		ft_rx(stack[0], size[0], 'a', 0);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		ft_rx(stack[1], size[1], 'b', 0);
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		ft_rrx(stack[0], size[0], 'a', 0);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		ft_rrx(stack[1], size[1], 'b', 0);
}

static void	ft_exec_ab_op(char *line, int **stack, size_t *size)
{
	if (ft_strncmp(line, "ss\n", 3) == 0)
	{
		ft_sx(stack[0], size[0], 'a', 0);
		ft_sx(stack[1], size[1], 'b', 0);
	}
	else if (ft_strncmp(line, "rr\n", 3) == 0)
	{
		ft_rx(stack[0], size[0], 'a', 0);
		ft_rx(stack[1], size[1], 'b', 0);
	}
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
	{
		ft_rrx(stack[0], size[0], 'a', 0);
		ft_rrx(stack[1], size[1], 'b', 0);
	}
}

void	ft_exec_ops(int **stack, size_t *size)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strncmp(line, "sa\n", 3) == 0 || ft_strncmp(line, "ra\n", 3) == 0
			|| ft_strncmp(line, "rra\n", 4) == 0
			|| ft_strncmp(line, "sb\n", 3) == 0
			|| ft_strncmp(line, "rb\n", 3) == 0
			|| ft_strncmp(line, "rrb\n", 4) == 0
			|| ft_strncmp(line, "pa\n", 3) == 0
			|| ft_strncmp(line, "pb\n", 3) == 0)
			ft_exec_x_op(line, stack, size);
		else if (ft_strncmp(line, "ss\n", 3) == 0
			|| ft_strncmp(line, "rr\n", 3) == 0
			|| ft_strncmp(line, "rrr\n", 4) == 0)
			ft_exec_ab_op(line, stack, size);
		else
			ft_cleanup(stack, 'e');
		free(line);
		line = get_next_line(0);
	}
}
