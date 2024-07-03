/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:10:12 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/03 10:31:15 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    ft_usleep(long time,t_philo *philo)
{
    long    start;

    start = get_time();
    while ((get_time() - start) < time && philo->ph_data->flag != 1)
        usleep(500);
}

long    get_time()
{
    struct  timeval tv;
    int             ret;

    ret = gettimeofday(&tv, NULL);
    if (ret)
        exit(1);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long time_of_ph(t_philo *philo)
{
    long time;

    pthread_mutex_lock(&philo->ph_data->mtx_to_print);
    time = get_time() - philo->ph_data->time;
    pthread_mutex_unlock(&philo->ph_data->mtx_to_print);
    return time;
}

// 1s -> 1000ms
// 1ms -> 1000us