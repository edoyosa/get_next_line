/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:35:54 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/10 20:57:18 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char *str_read, char *str_buf, size_t count)
{
	free(str_read);
	if (*str_buf == 0 || count == 0)
		free(str_buf);
}

char	*ft_reading_line(char *str_buf, char *str_read)
{
	if (!str_buf)
	{
		str_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!str_buf)
			return (0);
		ft_strlcpy(str_buf, str_read, BUFFER_SIZE + 1);
		str_buf[BUFFER_SIZE] = 0;
	}
	else
		str_buf = ft_strjoin(str_buf, str_read);
	return (str_buf);
}

char	*ft_new_buf(char *str_buf, size_t buf_length, unsigned int i)
{
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (buf_length - i));
	if (!temp)
		return (0);
	ft_strlcpy(temp, &str_buf[i + 1], buf_length - i);
	temp[buf_length - i - 1] = 0;
	free(str_buf);
	return (temp);
}

char	*ft_create_res(char *str_buf, char *res)
{
	unsigned int	i;
	size_t			buf_length;

	buf_length = ft_strlen(str_buf);
	i = 0;
	while (str_buf[i] != '\n' && str_buf[i] != 0)
		i++;
	if (str_buf[i])
		res = (char *)malloc(sizeof(char) * i + 1);
	else
		res = (char *)malloc(sizeof(char) * i);
	if (!res)
		return (0);
	ft_strlcpy(res, str_buf, i + 1);
	if (str_buf[i])
	{
		res[i] = '\n';
		str_buf = ft_new_buf(str_buf, buf_length, i);
	}
	else
		*str_buf = 0;
	return (res);
}

char	*get_next_line(int fd)
{
	char		*str_read;
	static char	*str_buf;
	char		*str_result;
	int			count;

	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	str_result = 0;
	str_read = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str_read)
		return (0);
	while (str_result == 0)
	{
		count = read(fd, str_read, BUFFER_SIZE);
		if (count < 0)
			return (0);
		str_read[count] = 0;
		str_buf = ft_reading_line(str_buf, str_read);
		if (!str_buf)
			return (0);
		if (count == 0 || ft_strchr(str_read, '\n'))
			str_result = ft_create_res(str_buf, str_result);
	}
	ft_free(str_read, str_buf, count);
	return (str_result);
}
