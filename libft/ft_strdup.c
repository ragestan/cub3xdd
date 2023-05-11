/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:53:37 by rel-mham          #+#    #+#             */
/*   Updated: 2022/10/13 23:11:21 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	char	*cpy_s1;
	int		s_s;
	int		i;

	i = 0;
	s_s = 0;
	while (s1[s_s] != '\0')
		s_s++;
	cpy_s1 = malloc(s_s * sizeof(char) + 1);
	if (!cpy_s1)
		return (NULL);
	while (s1[i])
	{
		cpy_s1[i] = s1[i];
		i++;
	}
	cpy_s1[i] = '\0';
	return (cpy_s1);
}
