/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:28:46 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/12 10:04:12 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	testee(t_philo *philo)
{
	if (philo->id_of_philo % 2)
	{
		pthread_mutex_unlock(philo->leftfork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);		
		pthread_mutex_unlock(philo->leftfork);
	}
}

void	ft_forks(t_philo *philo)
{
	if (philo->id_of_philo % 2)
	{
		pthread_mutex_lock(philo->leftfork);
		ft_printf1(time_of_ph(philo), philo, 1);
		pthread_mutex_lock(philo->right_fork);
		ft_printf1(time_of_ph(philo), philo, 2);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		ft_printf1(time_of_ph(philo), philo, 2);
		pthread_mutex_lock(philo->leftfork);
		ft_printf1(time_of_ph(philo), philo, 1);
	}
}

void	eat(t_philo *philo)
{
	ft_forks(philo);
	pthread_mutex_lock(&philo->ph_data->status);
	philo->old_time = get_time();
	if (philo->ph_data->flag != 1)
	{
		philo->status = 1;
		ft_printf(time_of_ph(philo), philo, 3);
	}
	pthread_mutex_unlock(&philo->ph_data->status);
	ft_usleep(philo->ph_data->time_to_eat, philo);
	pthread_mutex_lock(&philo->ph_data->mtx_eat);
	philo->eat--;
	pthread_mutex_unlock(&philo->ph_data->mtx_eat);
	testee(philo);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_data->status);
	if (philo->ph_data->flag != 1)
	{
		philo->status = 0;
		pthread_mutex_unlock(&philo->ph_data->status);
		ft_printf(time_of_ph(philo), philo, 4);
		ft_usleep(philo->ph_data->time_to_sleep, philo);
		return ;
	}
	pthread_mutex_unlock(&philo->ph_data->status);
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->ph_data->status);
	if (philo->ph_data->flag != 1)
	{
		philo->status = 0;
		ft_printf(time_of_ph(philo), philo, 5);
	}
	pthread_mutex_unlock(&philo->ph_data->status);
}

void	routine(t_philo	*philo)
{
	eat(philo);
	sleeping(philo);
	thinking(philo);
	if ( philo->ph_data->nb_of_philo % 2)
		ft_usleep((philo->ph_data->time_to_die - (get_time() - philo->old_time)) / 2, philo);
}
