/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:14:28 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/12 11:14:30 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdlib.h>

void	ft_cleanup(int **arr, char msg);
void	ft_fill_arr(int argc, char **argv, int **stack);
int		*ft_simplify_arr(int *stack, size_t size);
void	ft_sort_few(int **stack, size_t size);
void	ft_radix_sort(int **stack, size_t *size, size_t max_size);

void	ft_sx(int *arr, size_t size, char stack, int msg);
void	ft_px(int **arr, size_t *size, char stack, int msg);
void	ft_rx(int *arr, size_t size, char stack, int msg);
void	ft_rrx(int *arr, size_t size, char stack, int msg);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);

#endif
