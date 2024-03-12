/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:56:26 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/12 13:42:11 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*list[1024];
	t_list			*temp;
	char			*next_line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (make_list(list, fd))
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
	if (list[fd] == NULL)
		return (NULL);
	next_line = give_line(list[fd]);
	clear_list(&list[fd]);
	return (next_line);
}

int	make_list(t_list **list, int fd)
{
	char	*buffer;
	int		char_read;

	while (!new_line(list[fd]))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return (0);
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (!char_read)
		{
			free(buffer);
			buffer = NULL;
			return (0);
		}
		if (char_read < 0)
		{
			free(buffer);
			buffer = NULL;
			return (1);
		}
		buffer[char_read] = '\0';
		add_list(list, buffer, fd);
	}
	return (0);
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

// write main to test multiple file descriptors one line of each every time

// int main ()
// {
// 	int fd1 = open("test1.txt", O_RDONLY);
// 	int fd2 = open("test2.txt", O_RDONLY);
// 	char *line;

// 	line = get_next_line(fd1);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd3);
// 	printf("%s\n", line);
// 	free(line);
// 	close(fd1);
// 	close(fd2);
// }