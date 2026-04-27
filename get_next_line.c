/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsack <vsack@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 20:27:31 by vsack             #+#    #+#             */
/*   Updated: 2026/04/27 20:37:20 by vsack            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	char	*buf_local;
	ssize_t	bytes_read;

	bytes_read = 1;
	buf_local = malloc(BUFFER_SIZE + 1);
	if (!buf_local)
		return (NULL);
	while ((ft_strchr(stash, '\n') == NULL) && (bytes_read != 0))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buf_local);
			return (NULL);
		}
	}
}
