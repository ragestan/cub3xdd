/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-mham <rel-mham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:02:25 by rel-mham          #+#    #+#             */
/*   Updated: 2023/05/03 09:07:03 by rel-mham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char	*str)
{
	int					neg;
	int					i;
	unsigned long long	result;

	i = 0;
	result = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '\0')
		return (-1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		result = (result * 10) + (str[i++] - 48);
	if (result > 9223372036854775807 && neg > 0)
		return (-1);
	else if (result > 9223372036854775807 && neg < 0)
		return (0);
	return (result * neg);
}
