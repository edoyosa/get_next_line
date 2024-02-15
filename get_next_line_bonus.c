/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:12:46 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/15 11:42:19 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_n_line(char *str)
{
	int		i;
	char	*nline;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (0);
	nline = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (*nline == '\0')
	{
		free(nline);
		nline = 0;
	}
	str[i + 1] = '\0';
	return (nline);
}

char	*ft_reads(int fd, char *str, char *newline)
{
	int		ret;
	char	*char_tmp;

	ret = 1;
	while (ret != '\0')
	{
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == -1)
			return (0);
		else if (ret == 0)
			break ;
		str[ret] = '\0';
		if (!newline)
			newline = ft_strdup("");
		char_tmp = newline;
		newline = ft_strjoin(char_tmp, str);
		free(char_tmp);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*str[4096];
	char		*line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = ft_reads(fd, buf, str[fd]);
	free(buf);
	buf = 0;
	if (!line)
		return (0);
	str[fd] = ft_n_line(line);
	return (line);
}
