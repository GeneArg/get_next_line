/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:56:26 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/11 16:44:58 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	t_list			*temp;
	char			*next_line;
	char			buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, &buffer, 0) < 0)
	{
		while (list[fd])
		{
			temp = list[fd]->next;
			free(list[fd]->content);
			free(list[fd]);
			list[fd] = temp;
		}
		return (NULL);
	}
	make_list(list, fd);
	if (list[fd] == NULL)
		return (NULL);
	next_line = give_line(list[fd]);
	clear_list(&list[fd]);
	return (next_line);
}

void	make_list(t_list **list, int fd)
{
	char	*buffer;
	int		char_read;

	while (!new_line(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (!char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		add_list(list, buffer, fd);
	}
}

void	add_list(t_list **list, char *buffer, int fd)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	last = find_last(list[fd]);
	if (last == NULL)
		list[fd] = new;
	else
		last->next = new;
	new->content = buffer;
	new->next = NULL;
}

char	*give_line(t_list *list)
{
	char	*next;
	int		i;

	if (list == NULL)
		return (NULL);
	i = len_new_line(list);
	next = malloc(i + 1);
	if (next == NULL)
		return (NULL);
	copy_string(list, next);
	return (next);
}

void	clear_list(t_list **list)
{
	t_list	*clean;
	t_list	*last;
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (clean == NULL || buffer == NULL)
		return ;
	i = 0;
	j = 0;
	last = find_last(*list);
	while (last->content[i] && last->content[i] != '\n')
		++i;
	while (last->content[i] && last->content[++i])
		buffer[j++] = last->content[i];
	buffer[j] = '\0';
	clean->content = buffer;
	clean->next = NULL;
	release(list, clean, buffer);
}

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	return (0);
// }