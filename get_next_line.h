/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:01:53 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/12 13:38:31 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
int		make_list(t_list **list, int fd);
void	add_list(t_list **list, char *buffer);
char	*give_line(t_list *list);
void	clear_list(t_list **list);
void	release(t_list **list, t_list *clean, char *buffer);
int		len_new_line(t_list *list);
void	copy_string(t_list *list, char *str);
t_list	*find_last(t_list *list);
int		new_line(t_list *list);

#endif