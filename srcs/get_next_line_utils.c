/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:07:00 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/04 14:49:41 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*gnl_strdup(char	*s1)
{
	s1 = malloc(sizeof(char));
	if (!s1)
		return (NULL);
	s1[0] = '\0';
	return (s1);
}

char	*gnl_strjoin(char *s1, char const	*s2)
{
	char	*strfinal;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		s1 = gnl_strdup("");
	strfinal = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!strfinal)
		return (NULL);
	while (s1[++i] != '\0')
		strfinal[i] = s1[i];
	while (*s2)
	{
		strfinal[i++] = *s2;
		s2++;
	}
	strfinal[i] = '\0';
	free(s1);
	return (strfinal);
}

int	ft_strchr(char	*s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char )c)
			return (1);
		i++;
	}
	if ((char)c == '\0')
		return (1);
	return (0);
}
