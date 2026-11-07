/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wli-ting <wli-ting@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 12:53:54 by wli-ting          #+#    #+#             */
/*   Updated: 2026/09/18 13:40:00 by wli-ting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*arr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff[fd])
	{
		buff[fd] = ft_strdup("");
		if (!buff[fd])
			return (NULL);
	}
	buff[fd] = read_buffer(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	if (buff[fd][0] == '\0')
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	arr = get_buffer(buff[fd]);
	buff[fd] = get_leftover(buff[fd]);
	return (arr);
}

char	*read_buffer(int fd, char *buff)
{
	char	*stash;
	char	*temp;
	int		reading;

	stash = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!stash)
		return (NULL);
	reading = read(fd, stash, BUFFER_SIZE);
	while (reading > 0)
	{
		stash[reading] = '\0';
		temp = ft_strjoin(buff, stash);
		free(buff);
		buff = temp;
		if (ft_strchr(buff, DELIMITER))
			break ;
		reading = read(fd, stash, BUFFER_SIZE);
	}
	free(stash);
	if (reading < 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

char	*get_buffer(char *buff)
{
	char	*arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buff[i] && buff[i] != DELIMITER)
		i++;
	if (buff[i] == DELIMITER)
		i++;
	arr = malloc(sizeof(char) * (i + 1));
	if (!arr)
		return (NULL);
	while (j < i)
	{
		arr[j] = buff[j];
		j++;
	}
	arr[j] = '\0';
	return (arr);
}

char	*get_leftover(char *buff)
{
	char	*leftover;
	int		i;

	i = 0;
	while (buff[i] && buff[i] != DELIMITER)
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	i++;
	leftover = ft_substr(buff, i, ft_strlen(buff) - i);
	free(buff);
	return (leftover);
}
