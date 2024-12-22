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

typedef struct s_cost
{
	size_t	total;
	size_t	ra;
	size_t	rra;
	size_t	rb;
	size_t	rrb;
	char	rot;
}	t_cost;

void	ft_apply_strategy(int **stack, size_t *size, t_cost best_cost);
int		ft_check_sort(int **stack, size_t *size);
void	ft_cleanup(int **arr, char msg);
void	ft_dupcheck(int **stack, size_t size_a);
void	ft_fill_arr(int argc, char **argv, int **stack);
void	ft_find_bounds(int *stack, size_t size, int *bound);
size_t	ft_find_size(int argc, char **argv);

void	ft_sort_array(int **stack, size_t *size);
void	ft_sort_five(int **stack, size_t *size);
void	ft_sort_many(int **stack, size_t *size);

void	ft_sx(int **stack, size_t *size, int num, int msg);
void	ft_px(int **stack, size_t *size, int num, int msg);
void	ft_rx(int **stack, size_t *size, int num, int msg);
void	ft_rrx(int **stack, size_t *size, int num, int msg);

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);

#endif
