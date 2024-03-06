/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:56:26 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/06 15:18:13 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*list;
	char			*next_line;

	list = NULL;
	if (fd < 0 || read(fd, &next_line, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	make_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	clear_list(&list);
	return (next_line);
}

void	make_list(t_list **list, int fd)
{
	char	*buffer;
	int		char_read;
	
	while (!new_line(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (buffer == NULL)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] = '\0';
		add_list(list, buffer);
	}
}

void	add_list(t_list **list, char *buffer)
{
	t_list	*new;
	t_list	*last;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return ;
	last = find_last(*list);
	if (last == NULL)
		*list = new;
	else
		last->next = new;
	new->content = buffer;
	new->next = NULL;
}

char	*get_line(t_list *list)
{
	char	*next;
	int		i;

	if (list == NULL)
		return (NULL);
	i = len_new_line(list);
	next = malloc((i + 1) * sizeof(char));
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
	// if (last->content[i] == '\n')
	// 	++i;
	while (last->content[i])
		buffer[j++] = last->content[i++];
	buffer[j] = '\0';
	clean->content = buffer;
	clean->next = NULL;
	release(list, clean, buffer);
}

void	release(t_list **list, t_list *clean, char *buffer)
{
	t_list	*temp;
	
	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->content);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (clean->content[0])
		*list = clean;
	else
	{
		free(buffer);
		free(clean);
	}
}

int	len_new_line(t_list *list)
{
	int	i;
	int len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_string(t_list *list, char *str)
{
	int	i;
	int	j;

	if (list == NULL)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->content[i])
		{
			if (list->content[i] == '\n')
			{
				str[j++] = '\n';
				str[j] = '\0';
				return ;
			}
			str[j++] = list->content[i++];
		}
		list = list->next;
	}
	str[j] = '\0';
}

t_list	*find_last(t_list *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

int	new_line(t_list *list)
{
	int	i;
	
	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->content[i] && i < BUFFER_SIZE)
		{
			if (list->content[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	line = get_next_line(fd);
	printf("%s\n", line);
	return (0);
}