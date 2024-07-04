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
	ft_printf(time_of_ph(philo), philo,1);

	pthread_mutex_lock(philo->right_fork);   
	ft_printf(time_of_ph(philo), philo,2);
	ft_printf(time_of_ph(philo), philo,3);
	pthread_mutex_lock(&philo->ph_data->mtx_eat);
		philo->eat--;
	pthread_mutex_unlock(&philo->ph_data->mtx_eat);
	pthread_mutex_lock(&philo->ph_data->status);
	philo->status = 1;
	pthread_mutex_unlock(&philo->ph_data->status);
	pthread_mutex_lock(&philo->ph_data->mtx_to_time);
		philo->old_time = get_time();
	pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
	ft_usleep(philo->ph_data->time_to_eat,philo);
	pthread_mutex_unlock(philo->leftfork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->ph_data->status);
	philo->status = 0;
	pthread_mutex_unlock(&philo->ph_data->status);
}

void	sleeping(t_philo *philo)
{
	if (philo->ph_data->flag != 1)
	{
		ft_printf(time_of_ph(philo), philo,4);
		ft_usleep(philo->ph_data->time_to_sleep,philo);
	}
}

void	thinking(t_philo *philo)
{
	if (philo->ph_data->flag != 1)
		ft_printf(time_of_ph(philo), philo,5);
}