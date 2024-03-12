/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:56:26 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/12 13:42:29 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	t_list			*temp;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (make_list(&list, fd))
	{
		while (list)
		{
			temp = list->next;
			free(list->content);
			free(list);
			list = temp;
		}
		return (NULL);
	}
	if (list == NULL)
		return (NULL);
	next_line = give_line(list);
	clear_list(&list);
	return (next_line);
}

int	make_list(t_list **list, int fd)
{
	char	*buffer;
	int		char_read;

	while (!new_line(*list))
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
		add_list(list, buffer);
	}
	return (0);
}

void	add_list(t_list **list, char *buffer)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
	{
		free(buffer);
		return ;
	}
	last = find_last(*list);
	if (last == NULL)
		*list = new;
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
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	clean = malloc(sizeof(t_list));
	if (buffer == NULL || clean == NULL)
		return ;
	last = find_last(*list);
	i = 0;
	j = 0;
	while (last->content[i] && last->content[i] != '\n')
		++i;
	while (last->content[i] && last->content[++i])
		buffer[j++] = last->content[i];
	buffer[j] = '\0';
	clean->content = buffer;
	clean->next = NULL;
	release(list, clean, buffer);
}

// write main to test with linked lists.

// int main()
// {
// 	int fd = open("test.txt", O_RDONLY);
// 	char *line;
// 	int no = 1;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%i: %s", no, line);
// 		free(line);
// 		line = get_next_line(fd);
// 		no++;
// 	}
// 	close(fd);
// 	return (0);
// }