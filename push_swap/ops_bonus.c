/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:46:16 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/09 13:46:19 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	ft_sx(int **stack, size_t *size, int num, int msg)
{
	int	tmp;

	if (num == 0 && msg == 1)
		ft_printf("sa\n");
	else if (num == 1 && msg == 1)
		ft_printf("sb\n");
	else if (num == 2)
	{
		if (msg == 1)
			ft_printf("ss\n");
		ft_sx(stack, size, 0, 0);
		num = 1;
	}
	if (size[num] < 2)
		return ;
	tmp = stack[num][0];
	stack[num][0] = stack[num][1];
	stack[num][1] = tmp;
}

static void	ft_px_core(int *dst, int *src, size_t *dst_size, size_t *src_size)
{
	size_t	i;

	if (*src_size < 1)
		return ;
	i = *dst_size;
	while (i > 0)
	{
		dst[i] = dst[i - 1];
		i--;
	}
	dst[0] = src[0];
	i = 0;
	while (i < *src_size - 1)
	{
		src[i] = src[i + 1];
		i++;
	}
	*dst_size += 1;
	*src_size -= 1;
}

void	ft_px(int **stack, size_t *size, int num, int msg)
{
	if (num == 0)
	{
		if (msg == 1)
			ft_printf("pa\n");
		ft_px_core(stack[0], stack[1], &size[0], &size[1]);
	}
	else
	{
		if (msg == 1)
			ft_printf("pb\n");
		ft_px_core(stack[1], stack[0], &size[1], &size[0]);
	}
}

void	ft_rx(int **stack, size_t *size, int num, int msg)
{
	int		tmp;
	size_t	i;

	if (num == 0 && msg == 1)
		ft_printf("ra\n");
	else if (num == 1 && msg == 1)
		ft_printf("rb\n");
	else if (num == 2)
	{
		if (msg == 1)
			ft_printf("rr\n");
		ft_rx(stack, size, 0, 0);
		num = 1;
	}
	if (size[num] < 2)
		return ;
	tmp = stack[num][0];
	i = 0;
	while (i < size[num] - 1)
	{
		stack[num][i] = stack[num][i + 1];
		i++;
	}
	stack[num][i] = tmp;
}

void	ft_rrx(int **stack, size_t *size, int num, int msg)
{
	int		tmp;
	size_t	i;

	if (num == 0 && msg == 1)
		ft_printf("rra\n");
	else if (num == 1 && msg == 1)
		ft_printf("rrb\n");
	else if (num == 2)
	{
		if (msg == 1)
			ft_printf("rrr\n");
		ft_rrx(stack, size, 0, 0);
		num = 1;
	}
	if (size[num] < 2)
		return ;
	i = size[num] - 1;
	tmp = stack[num][i];
	while (i > 0)
	{
		stack[num][i] = stack[num][i - 1];
		i--;
	}
	stack[num][0] = tmp;
}
