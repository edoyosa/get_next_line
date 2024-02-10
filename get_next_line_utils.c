/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:39:32 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/10 20:25:04 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	size_src;

	size_src = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (size_src);
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (size_src);
}

char	ft_strchr(char *s, int c)
{
	unsigned char	uc;

	uc = c;
	while (*s && uc != *s)
		s++;
	if (!(*s) && uc)
		return (0);
	return ((char)uc);
}

size_t	ft_strlcat(char *dst, char *src, size_t size)
{
	size_t	dstlen;
	size_t	i;
	size_t	srclen;

	i = 0;
	if (size == 0)
	{
		srclen = ft_strlen(src);
		return (srclen);
	}
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	while ((i + dstlen) < (size - 1) && src[i])
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	return (dstlen + srclen);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	totlen;
	size_t	s1_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	totlen = s1_len + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * totlen + 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s1, totlen + 1);
	str[s1_len] = '\0';
	ft_strlcat(str, s2, totlen + 1);
	str[totlen] = '\0';
	free (s1);
	return (str);
}
