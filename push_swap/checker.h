/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 12:55:37 by gdosch            #+#    #+#             */
/*   Updated: 2024/12/05 12:55:38 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include <limits.h>
# include <stdlib.h>

void	ft_cleanup(int **arr, char msg);
void	ft_fill_arr(int argc, char **argv, int **stack, size_t *size);
size_t	ft_find_size(int argc, char **argv);

void	ft_sx(int *arr, size_t size, int stack, int msg);
void	ft_px(int **arr, size_t *size, int stack, int msg);
void	ft_rx(int *arr, size_t size, int stack, int msg);
void	ft_rrx(int *arr, size_t size, int stack, int msg);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);

#endif
