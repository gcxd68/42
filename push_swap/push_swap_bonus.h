/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:37 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/05 12:55:38 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_BONUS_H
# define PUSH_SWAP_BONUS_H

# include <limits.h>
# include <stdlib.h>

void	ft_cleanup(int **arr, char msg);
void	ft_dupcheck(int **stack, size_t size_a);
void	ft_fill_arr(int argc, char **argv, int **stack);
size_t	ft_find_size(int argc, char **argv);

void	ft_sx(int **stack, size_t *size, int num, int msg);
void	ft_px(int **stack, size_t *size, int num, int msg);
void	ft_rx(int **stack, size_t *size, int num, int msg);
void	ft_rrx(int **stack, size_t *size, int num, int msg);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);

#endif
