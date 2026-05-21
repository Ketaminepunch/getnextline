/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsack <vsack@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 18:27:56 by vsack             #+#    #+#             */
/*   Updated: 2026/05/05 19:13:45 by vsack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	ssize_t	read_bytes;
	char	*tmp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		if (!tmp)
			return (NULL);
		stash = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*newstash;

	j = 0;
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	newstash = malloc(sizeof(char) * (ft_strlen(stash) - i));
	if (!newstash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	while (stash[i])
		newstash[j++] = stash[i++];
	newstash[j] = '\0';
	free(stash);
	return (newstash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (!stash[fd] || !ft_strchr(stash[fd], '\n'))
		stash[fd] = read_and_stash(fd, stash[fd], buffer);
	free(buffer);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
/*
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	read_files(int argc, int *fds)
{
	int		active;
	int		i;
	char	*line;

	active = 1;
	while (active)
	{
		active = 0;
		i = 1;
		while (i < argc)
		{
			line = get_next_line(fds[i]);
			if (line)
			{
				printf("File %d: %s", i, line);
				free(line);
				active = 1;
			}
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	int	fds[1024];
	int	i;

	if (argc < 2 || argc > 1023)
		return (1);
	i = 1;
	while (i < argc)
	{
		fds[i] = open(argv[i], O_RDONLY);
		i++;
	}
	read_files(argc, fds);
	i = 1;
	while (i < argc)
	{
		if (fds[i] >= 0)
			close(fds[i]);
		i++;
	}
	return (0);
}
*/