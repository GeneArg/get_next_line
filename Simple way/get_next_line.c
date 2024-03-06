/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagranat <eagranat@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:00:22 by eagranat          #+#    #+#             */
/*   Updated: 2024/03/01 16:45:30 by eagranat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	line[5000000];
	char	buf;
	int		i;
	int		j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	j = read(fd, &buf, 1);
	i = 0;
	while (j > 0)
	{
		line[i] = buf;
		i++;
		if (buf == '\n')
			break ;
		j = read(fd, &buf, 1);
	}
	line[i] = '\0';
	if (i == 0 && j <= 0)
		return (NULL);
	return (ft_strdup(line));
}

// #include <stdio.h>
// #include <fcntl.h>

// int main()
// {
// 	int fd;
// 	int fd1;
// 	char *line;

// 	fd = open("test.txt", O_RDONLY);
// 	fd1 = open("1.txt", O_RDONLY);
// 	//test read on stdin
// 	// line = get_next_line(0);
// 	// printf("%s", line);
// 	// free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	free(line);
// 	// line = get_next_line(fd);
// 	// printf("%s\n", line);
// 	// free(line);
// 	close(fd);
// 	close(fd1);
// 	return (0);
// }