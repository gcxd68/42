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
# include <ctype.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <bsd/string.h>

void	ft_sx(int *arr, size_t *size);
void	ft_px(int *arr1, int *arr2, size_t *size_a1, size_t *size_a2);
void	ft_rx(int *arr, size_t *size);
void	ft_rrx(int *arr, size_t *size);
void	ft_ss(int *a, int *b, size_t *size_a, size_t *size_b);
void	ft_rr(int *a, int *b, size_t *size_a, size_t *size_b);
void	ft_rrr(int *a, int *b, size_t *size_a, size_t *size_b);

void	*ft_calloc(size_t nmemb, size_t size);
int		ft_isdigit(int c);
int		ft_printf(const char *format, ...);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*get_next_line(int fd);

#endif
