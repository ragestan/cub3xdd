/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:41:11 by rel-mham          #+#    #+#             */
/*   Updated: 2022/10/20 11:55:36 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char	const	*s, unsigned int start, size_t	len)
{
	unsigned int	i;
	unsigned int	j;
	char			*substr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len + start >= ft_strlen(s))
		len = ft_strlen(s) - start;
	substr = malloc(sizeof (char) * (len + 1));
	if (!substr)
		return (NULL);
	while (s[start] != '\0' && j < len)
	{
		substr[j] = s[start];
		j++;
		start++;
	}
	substr[j] = '\0';
	return (substr);
}
