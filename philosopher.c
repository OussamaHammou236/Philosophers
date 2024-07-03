/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/03 10:45:31 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *handler(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    philo->eat = philo->ph_data->eat;
    philo->old_time = get_time();
    philo->status = 0;
    philo->fg = 0;
    if(philo->id_of_philo % 2)
        ft_usleep(philo->ph_data->time_to_eat - 10,philo);
    while(1)
    {
        if(philo->status == 5)
            printf("%ld philo nb %d is died\n",time_of_ph(philo), philo->id_of_philo);
        if (philo->ph_data->flag == 1)
            return (NULL);
        if (philo->fg == 1)
            return (philo->ph_data->flag1++,NULL);
        eat(philo);
        sleeping(philo);
        thinking(philo);
    }
    return NULL;
}

void *tr(void *arg)
{
    t_philo *philo;
    int i;

    i     = 0;
    philo = arg;
    ft_usleep(philo->ph_data->time_to_die - 10,philo);
    while(1)
    {
        if (i == philo->ph_data->nb_of_philo)
            i = 0;
        if(philo->ph_data->flag1 >= philo->ph_data->nb_of_philo)
            return NULL ;
        pthread_mutex_lock(&philo->ph_data->mtx_to_time);  
        if (get_time() - philo[i].old_time > philo[i].ph_data->time_to_die && philo->status != 1)
        {
            // printf("%ld philo nb %d is died\n",time_of_ph(&philo[i]), philo[i].id_of_philo);
            philo[i].status = 5;
            philo->ph_data->flag = 1;
            pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
            return NULL;
        }
        pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
        pthread_mutex_lock(&philo->ph_data->mtx_eat); 
        if (philo[i].eat < 0 && philo[i].ph_data->flag2)
            philo[i].fg = 1;
        pthread_mutex_unlock(&philo->ph_data->mtx_eat);
        i++;
    }
    return NULL;
}

int main(int ac,char **av)
{
    if(ac != 5 && ac != 6)
        return 0;
    t_data data;
    t_philo *philo;
    data.nb_of_philo = ft_atoi(av[1]);
    // convert milliseconds to microseconds
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    data.flag2 = 0;
    if(ac == 6)
    {
        data.eat = ft_atoi(av[5]);
        data.flag2 = 1;
    }
    philo = malloc(data.nb_of_philo * sizeof(t_philo));
    initialization(&data,philo);
    thread_creat(&data,philo);
    join_thread(data,philo);
    
}