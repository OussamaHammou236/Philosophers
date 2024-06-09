/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:39:59 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/09 20:13:10 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_error(char *str)
{
    write(1,str,ft_strlen(str));
    exit(1);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	long	r;

	i = 0;
	r = 0;
	s = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	if (str[i] == '\0')
		ft_error("error\n");
	while (str[i] >= '0' && str[i] <= '9' && str[i])
	{
		r = r * 10 + (str[i] - 48);
		i++;
		if ((r * s) > 2147483647 || (r * s) < -2147483648)
			ft_error("error\n");
	}
	if (str[i] != '\0')
		ft_error("error\n");
	return ((int)r * s);
}
