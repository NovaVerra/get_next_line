/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 14:05:05 by llee              #+#    #+#             */
/*   Updated: 2018/11/13 10:56:37 by llee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		copy_to_line(char **arr, char **line, int fd, int file)
{
	char	*temp;
	int		counter;

	counter = 0;
	while (arr[fd][counter] != '\0' && arr[fd][counter] != '\n')
		counter++;
	if (arr[fd][counter] == '\0')
	{
		if (file == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(arr[fd]);
		ft_strdel(&arr[fd]);
	}
	else if (arr[fd][counter] == '\n')
	{
		*line = ft_strsub(arr[fd], 0, counter);
		temp = ft_strdup(arr[fd] + counter + 1);
		free(arr[fd]);
		arr[fd] = temp;
		if (arr[fd][0] == '\0')
			ft_strdel(&arr[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			file;
	char		buf[BUFF_SIZE];
	char		*temp;
	static char	*arr[4864];

	if (fd < 0 || line == NULL)
		return (-1);
	while ((file = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[file] = '\0';
		if (arr[fd] == NULL)
			arr[fd] = ft_strnew(1);
		temp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = temp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (file < 0)
		return (-1);
	else if (file == 0 && (arr[fd] == NULL || arr[fd][0] == '\0'))
		return (0);
	return (copy_to_line(arr, line, fd, file));
}
