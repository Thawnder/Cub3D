/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldeville <ldeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 14:13:06 by bpleutin          #+#    #+#             */
/*   Updated: 2023/11/15 11:21:26 by ldeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
size_t	ft_strlen2(char *str);
char	*ft_strjoin2(char *s1, char *s2);
char	*ft_strchr2(char *str, int n);
char	*ft_strdup2(char *str);
char	*ft_substr2(char *s, unsigned int start, size_t len);

#endif