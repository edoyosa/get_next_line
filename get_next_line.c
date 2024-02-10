/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:35:54 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/10 06:39:30 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char *str_read, char *str_buf, size_t count)
{
	free(str_read);
	if ((*str_buf == 0 || count == 0) && str_buf)
		free(str_buf);
}

char	*ft_first_buf(char *str_buf, char *str_read)
{
	str_buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str_buf)
		return (0);
	ft_strlcpy(str_buf, str_read, BUFFER_SIZE + 1);
	str_buf[BUFFER_SIZE] = 0;
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
	str_buf = temp;
	return (temp);
}

char	*ft_create_res(char *str_buf)
{
	unsigned int	i;
	char			*res;
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
	size_t		count;

	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (0);
	count = 0;
	str_result = 0;
	str_read = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str_read)
		return (0);
	while (str_result == 0)
	{
		count = read(fd, str_read, BUFFER_SIZE);
		str_read[count] = 0;
		if (!str_buf)
			str_buf = ft_first_buf(str_buf, str_read);
		else if (count != 0)
			str_buf = ft_strjoin(str_buf, str_read);
		if (count == 0 || !str_buf || ft_strchr(str_buf, '\n'))
			str_result = ft_create_res(str_buf);
	}
	ft_free(str_read, str_buf, count);
	return (str_result);
}
