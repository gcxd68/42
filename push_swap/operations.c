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

#include "checker.h"

void	ft_sx(int *arr, size_t size, char stack, int msg)
{
	int	tmp;

	if (msg == 1 && stack == 'a')
		ft_printf("sa\n");
	else if (msg == 1)
		ft_printf("sb\n");
	if (size < 2)
		return ;
	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
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

void	ft_px(int **arr, size_t *size, char stack, int msg)
{
	if (stack == 'a')
	{
		if (msg == 1)
			ft_printf("pa\n");
		ft_px_core(arr[0], arr[1], &size[0], &size[1]);
	}
	else
	{
		if (msg == 1)
			ft_printf("pb\n");
		ft_px_core(arr[1], arr[0], &size[1], &size[0]);
	}
}

void	ft_rx(int *arr, size_t size, char stack, int msg)
{
	int		tmp;
	size_t	i;

	if (msg == 1 && stack == 'a')
		ft_printf("ra\n");
	else if (msg == 1)
		ft_printf("rb\n");
	if (size < 2)
		return ;
	tmp = arr[0];
	i = 0;
	while (i < size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = tmp;
}

void	ft_rrx(int *arr, size_t size, char stack, int msg)
{
	int		tmp;
	size_t	i;

	if (msg == 1 && stack == 'a')
		ft_printf("rra\n");
	else if (msg == 1)
		ft_printf("rrb\n");
	if (size < 2)
		return ;
	i = size - 1;
	tmp = arr[i];
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = tmp;
}
