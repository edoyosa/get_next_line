/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:12:46 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/15 13:01:49 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_handle_nl(char *str_result)
{
	int		i;
	char	*new_line;

	i = 0;
	while (str_result[i] != '\0' && str_result[i] != '\n')
		i++;
	if (str_result[i] == '\0')
		return (0);
	new_line = ft_substr(str_result, i + 1, ft_strlen(str_result) - i);
	if (*new_line == '\0')
	{
		free(new_line);
		new_line = 0;
	}
	while (str_result[++i])
		str_result[i] = '\0';
	return (new_line);
}

static char	*ft_str_read(int fd, char *str_read, char *str_buf)
{
	int		nbytes;
	char	*temp;

	nbytes = 1;
	while (nbytes != '\0')
	{
		nbytes = read(fd, str_read, BUFFER_SIZE);
		if (nbytes == -1)
			return (0);
		else if (nbytes > 0)
		{
			str_read[nbytes] = '\0';
			if (!str_buf)
				str_buf = ft_strdup("");
			temp = str_buf;
			str_buf = ft_strjoin(temp, str_read);
			free(temp);
		}
		if (nbytes == 0 || ft_strchr(str_read, '\n'))
			nbytes = '\0';
	}
	return (str_buf);
}

char	*get_next_line(int fd)
{
	static char	*str_buf;
	char		*str_read;
	char		*str_result;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (0);
	str_read = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!str_read)
		return (0);
	str_result = ft_str_read(fd, str_read, str_buf);
	free(str_read);
	str_read = 0;
	if (!str_result)
		return (0);
	str_buf = ft_handle_nl(str_result);
	return (str_result);
}
