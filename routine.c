/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:28:46 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/03 10:58:03 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->leftfork);
	printf("%ld philo nb %d  has taken a leftfork \n",time_of_ph(philo),philo->id_of_philo);

	pthread_mutex_lock(philo->right_fork);   
	printf("%ld philo nb %d  has taken a right_fork \n",time_of_ph(philo), philo->id_of_philo);
	printf("%ld philo nb %d  is eating \n",time_of_ph(philo) , philo->id_of_philo);
	pthread_mutex_lock(&philo->ph_data->mtx_eat);
		philo->eat--;
	pthread_mutex_unlock(&philo->ph_data->mtx_eat);
	philo->status = 1;
	pthread_mutex_lock(&philo->ph_data->mtx_to_time);
		philo->old_time = get_time();
	pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
	ft_usleep(philo->ph_data->time_to_eat,philo);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->right_fork);
	philo->status = 0;
}

void	sleeping(t_philo *philo)
{
	if (philo->ph_data->flag != 1)
		printf("%ld philo nb %d  is sleeping \n", time_of_ph(philo),philo->id_of_philo);
	ft_usleep(philo->ph_data->time_to_sleep,philo);
}

void	thinking(t_philo *philo)
{
	if (philo->ph_data->flag != 1)
		printf("%ld philo nb %d  is thinking \n", time_of_ph(philo),philo->id_of_philo);
}