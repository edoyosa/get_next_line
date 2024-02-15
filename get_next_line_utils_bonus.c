/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebellini <ebellini@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:44:54 by ebellini          #+#    #+#             */
/*   Updated: 2024/02/15 11:46:02 by ebellini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	uc;

	uc = c;
	while (*s && uc != *s)
		s++;
	if (!(*s) && uc)
		return (0);
	return ((char *)s);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	slength;

	i = 0;
	if (!s)
		return (0);
	slength = ft_strlen(s);
	if (start >= slength)
		str = ft_strdup("");
	else if (len <= slength - start)
		str = (char *)malloc(sizeof(char) * (len + 1));
	else
		str = (char *)malloc(sizeof(char) * (slength - start + 1));
	if (!str)
		return (0);
	while (i < len && (i + start) < slength)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (0);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*str;

	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (0);
	while (*s)
	{
		*str = *s;
		str++;
		s++;
	}
	*str = 0;
	return (str);
}
