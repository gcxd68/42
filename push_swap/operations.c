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

static void	ft_px_core(int *d_arr, int *s_arr, size_t *d_size, size_t *s_size)
{
	size_t	i;

	if (*s_size < 1)
		return ;
	i = *d_size;
	while (i > 0)
	{
		d_arr[i] = d_arr[i - 1];
		i--;
	}
	d_arr[0] = s_arr[0];
	i = 0;
	while (i < *s_size - 1)
	{
		s_arr[i] = s_arr[i + 1];
		i++;
	}
	*d_size += 1;
	*s_size -= 1;
}

void	ft_px(int **arr, size_t *size, char stack, int msg)
{
	int		*src_arr;
	int		*dest_arr;
	size_t	*src_size;
	size_t	*dest_size;

	if (stack == 'a')
	{
		if (msg == 1)
			ft_printf("pa\n");
		dest_arr = arr[0];
		src_arr = arr[1];
		dest_size = &size[0];
		src_size = &size[1];
	}
	else
	{
		if (msg == 1)
			ft_printf("pb\n");
		dest_arr = arr[1];
		src_arr = arr[0];
		dest_size = &size[1];
		src_size = &size[0];
	}
	ft_px_core(dest_arr, src_arr, dest_size, src_size);
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
