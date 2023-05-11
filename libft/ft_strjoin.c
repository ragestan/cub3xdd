/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:51:57 by rel-mham          #+#    #+#             */
/*   Updated: 2022/10/19 13:30:51 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	char	*strfinal;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	strfinal = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!strfinal)
		return (NULL);
	while (s1[i] != '\0')
	{
		strfinal[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		strfinal[i] = *s2;
		s2++;
		i++;
	}
	strfinal[i] = '\0';
	return (strfinal);
}
