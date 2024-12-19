/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:27 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/05 12:55:29 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

static void	ft_exec_x_op(char *line, int **stack, size_t *size)
{
	if (ft_strncmp(line, "sa\n", 3) == 0)
		ft_sx(stack, size, 0, 0);
	else if (ft_strncmp(line, "sb\n", 3) == 0)
		ft_sx(stack, size, 1, 0);
	else if (ft_strncmp(line, "pa\n", 3) == 0)
		ft_px(stack, size, 0, 0);
	else if (ft_strncmp(line, "pb\n", 3) == 0)
		ft_px(stack, size, 1, 0);
	else if (ft_strncmp(line, "ra\n", 3) == 0)
		ft_rx(stack, size, 0, 0);
	else if (ft_strncmp(line, "rb\n", 3) == 0)
		ft_rx(stack, size, 1, 0);
	else if (ft_strncmp(line, "rra\n", 4) == 0)
		ft_rrx(stack, size, 0, 0);
	else if (ft_strncmp(line, "rrb\n", 4) == 0)
		ft_rrx(stack, size, 1, 0);
}

static void	ft_exec_ab_op(char *line, int **stack, size_t *size)
{
	if (ft_strncmp(line, "ss\n", 3) == 0)
		ft_sx(stack, size, 2, 0);
	else if (ft_strncmp(line, "rr\n", 3) == 0)
		ft_rx(stack, size, 2, 0);
	else if (ft_strncmp(line, "rrr\n", 4) == 0)
		ft_rrx(stack, size, 2, 0);
}

static void	ft_exec_ops(int **stack, size_t *size)
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

static void	ft_check_arr(int **stack, size_t *size)
{
	size_t	i;

	if (!stack || !stack[0])
		ft_cleanup(stack, 'e');
	i = 0;
	while (i < size[0] - 1 && stack[0][i] < stack[0][i + 1])
		i++;
	if (i == size[0] - 1 && size[1] == 0)
		ft_cleanup(stack, 'o');
	ft_cleanup(stack, 'k');
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
	ft_fill_arr(argc, argv, stack, size);
	ft_exec_ops(stack, size);
	ft_check_arr(stack, size);
	return (0);
}
