/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/08/09 19:20:41 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_printf(long time, t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->ph_data->mtx_to_print);
	if (flag == 0)
		printf("%ld %d died\n", time, philo->id_of_philo);
	else if (flag == 3)
		printf("%ld %d is eating \n", time, philo->id_of_philo);
	else if (flag == 4)
		printf("%ld %d is sleeping\n", time, philo->id_of_philo);
	else if (flag == 5)
		printf("%ld %d is thinking\n", time, philo->id_of_philo);
	pthread_mutex_unlock(&philo->ph_data->mtx_to_print);
}

void	*handler(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initialization_philo(philo);
	if (philo->id_of_philo % 2 == 0 && philo->ph_data->nb_of_philo % 2 == 0)
		ft_usleep(philo->ph_data->time_to_eat - 10, philo);
	while (1 && philo->ph_data->nb_of_philo > 1)
	{
		pthread_mutex_lock(&philo->ph_data->status);
		if (philo->status == 5)
			ft_printf(time_of_ph(philo), philo, 0);
		if (philo->ph_data->flag == 1)
			return (pthread_mutex_unlock(&philo->ph_data->status), NULL);
		pthread_mutex_unlock(&philo->ph_data->status);
		pthread_mutex_lock(&philo->ph_data->mtx_eat);
		if (philo->fg == 1)
		{
			philo->ph_data->flag1++;
			return (pthread_mutex_unlock(&philo->ph_data->mtx_eat), NULL);
		}
		pthread_mutex_unlock(&philo->ph_data->mtx_eat);
		routine(philo);
	}
	return (NULL);
}

int	etc_of_tr(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->ph_data->status);
	if (get_time() - philo[i].old_time > philo[i].ph_data->time_to_die
		&& philo[i].status != 1)
	{
		philo->ph_data->flag = 1;
		philo[i].status = 5;
		pthread_mutex_unlock(&philo->ph_data->status);
		return (1);
	}
	pthread_mutex_unlock(&philo->ph_data->status);
	return (0);
}

void	*tr(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = arg;
	ft_usleep(philo->ph_data->time_to_die - 10, philo);
	while (1)
	{
		if (i == philo->ph_data->nb_of_philo)
			i = 0;
		pthread_mutex_lock(&philo->ph_data->mtx_eat);
		if (philo->ph_data->flag1 >= philo->ph_data->nb_of_philo)
			return (pthread_mutex_unlock(&philo->ph_data->mtx_eat), NULL);
		pthread_mutex_unlock(&philo->ph_data->mtx_eat);
		if (etc_of_tr(philo, i) == 1)
			return (NULL);
		pthread_mutex_lock(&philo->ph_data->mtx_eat);
		if (philo[i].eat < 0 && philo[i].ph_data->flag2)
			philo[i].fg = 1;
		pthread_mutex_unlock(&philo->ph_data->mtx_eat);
		i++;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (0);
	data.nb_of_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.flag2 = 0;
	if (ac == 6)
	{
		data.eat = ft_atoi(av[5]);
		data.flag2 = 1;
	}
	if (data.time_to_die < 0 || data.time_to_eat < 0 || data.time_to_sleep < 0
		|| data.nb_of_philo <= 0 || (data.flag2 && data.eat <= 0))
		return (ft_error("error\n"));
	philo = malloc(data.nb_of_philo * sizeof(t_philo));
	initialization(&data, philo);
	thread_creat(&data, philo);
	join_thread(data, philo);
	free_memory(philo);
	return (0);
}
