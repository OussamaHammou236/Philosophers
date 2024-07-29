/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 21:24:55 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/29 22:18:32 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	free_memory(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].ph_data->nb_of_philo)
	{
		free(philo[i].leftfork);
		free(&philo[i]);
		i++;
	}
}
