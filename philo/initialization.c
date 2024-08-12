/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:23:12 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/09 19:20:17 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	join_thread(t_data data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_join(philo[0].ph_data->tr, NULL);
	while (data.nb_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
		data.nb_of_philo--;
	}
}

void	initialization(t_data *data, t_philo *philo)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (nb < data->nb_of_philo)
		philo[nb++].leftfork = malloc(sizeof(pthread_mutex_t));
	while (i < data->nb_of_philo)
	{
		pthread_mutex_init(philo[i].leftfork, NULL);
		if (i == data->nb_of_philo - 1)
			philo[i].right_fork = philo[0].leftfork;
		else
			philo[i].right_fork = philo[i + 1].leftfork;
		philo[i].id_of_philo = i + 1;
		philo[i].ph_data = data;
		i++;
	}
	pthread_mutex_init(&philo[0].ph_data->mtx_to_time, NULL);
	pthread_mutex_init(&philo[0].ph_data->mtx_to_print, NULL);
	pthread_mutex_init(&philo[0].ph_data->mtx_eat, NULL);
	pthread_mutex_init(&philo[0].ph_data->mtx_flag, NULL);
	pthread_mutex_init(&philo[0].ph_data->status, NULL);
}

void	thread_creat(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	data->time = get_time();
	data->flag = 0;
	data->flag1 = 0;
	while (i < data->nb_of_philo)
	{
		pthread_create(&philo[i].thread, NULL, handler, &philo[i]);
		i++;
	}
	pthread_create(&data->tr, NULL, tr, philo);
}

void	initialization_philo(t_philo *philo)
{
	philo->eat = philo->ph_data->eat;
	philo->status = 0;
	philo->fg = 0;
	philo->old_time = get_time();
	if (philo->ph_data->nb_of_philo == 1)
	{
		ft_usleep(philo->ph_data->time_to_die + 1, philo);
		ft_printf(time_of_ph(philo), philo, 0);
	}
}

void	ft_printf1(long time, t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->ph_data->status);
	if (philo->ph_data->flag == 1)
	{
		pthread_mutex_unlock(&philo->ph_data->status);
		return ;
	}
	pthread_mutex_unlock(&philo->ph_data->status);
	pthread_mutex_lock(&philo->ph_data->mtx_to_print);
	if (flag == 1)
		printf("%ld %d has taken a fork\n", time,
			philo->id_of_philo);
	if (flag == 2)
		printf("%ld %d has taken a fork\n", time,
			philo->id_of_philo);
	pthread_mutex_unlock(&philo->ph_data->mtx_to_print);
}
