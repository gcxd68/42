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

void	ft_sx(int *arr, size_t *size)
{
	int	tmp;

	if (*size < 2)
		return ;
	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}

void	ft_px(int *arr1, int *arr2, size_t *size_a1, size_t *size_a2)
{
	size_t	i;

	if (*size_a2 < 1)
		return ;
	i = *size_a1;
	while (i > 0)
	{
		arr1[i] = arr1[i - 1];
		i--;
	}
	arr1[0] = arr2[0];
	i = 0;
	while (i < *size_a2 - 1)
	{
		arr2[i] = arr2[i + 1];
		i++;
	}
	*size_a1 += 1;
	*size_a2 -= 1;
}

void	ft_rx(int *arr, size_t *size)
{
	int		tmp;
	size_t	i;

	if (*size < 2)
		return ;
	tmp = arr[0];
	i = 0;
	while (i < *size - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[i] = tmp;
}

void	ft_rrx(int *arr, size_t *size)
{
	int		tmp;
	size_t	i;

	if (*size < 2)
		return ;
	i = *size - 1;
	tmp = arr[i];
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = tmp;
}

void	ft_ss(int *a, int *b, size_t *size_a, size_t *size_b)
{
	ft_sx(a, size_a);
	ft_sx(b, size_b);
}

void	ft_rr(int *a, int *b, size_t *size_a, size_t *size_b)
{
	ft_rx(a, size_a);
	ft_rx(b, size_b);
}

void	ft_rrr(int *a, int *b, size_t *size_a, size_t *size_b)
{
	ft_rrx(a, size_a);
	ft_rrx(b, size_b);
}
