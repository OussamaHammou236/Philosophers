/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/26 10:41:57 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->leftfork);
    gettimeofday(&philo->ph_data->first_time,0);
    printf("%ld philo nb %d  has taken a leftfork \n",philo->ph_data->first_time.tv_usec - philo->ph_data->time,philo->id_of_philo);
    pthread_mutex_lock(philo->right_fork);
    gettimeofday(&philo->ph_data->first_time,0);
    printf("%ld philo nb %d  has taken a right_fork \n",philo->ph_data->first_time.tv_usec - philo->ph_data->time, philo->id_of_philo);
    gettimeofday(&philo->ph_data->first_time,0);
    printf("%ld philo nb %d  is eating \n",philo->ph_data->first_time.tv_usec - philo->ph_data->time, philo->id_of_philo);
    usleep(philo->ph_data->time_to_eat);
    pthread_mutex_unlock(philo->leftfork);
    pthread_mutex_unlock(philo->right_fork); 
}

void sleeping(t_philo *philo)
{
    gettimeofday(&philo->ph_data->first_time,0);
    printf("%ld philo nb %d  is sleeping \n", philo->ph_data->first_time.tv_usec - philo->ph_data->time,philo->id_of_philo);
    usleep(philo->ph_data->time_to_sleep);
}

void thinking(t_philo *philo)
{
    printf("philo nb %d  is thinking \n",philo->id_of_philo);
     
}

void *handler(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    int i = 0;
    if(philo->id_of_philo % 2)
        usleep(philo->ph_data->time_to_eat - 10);
    eat(philo);
    sleeping(philo);
    return NULL;
}

void join_thread(t_data data,t_philo *philo)
{
    int i;

    i = 0;
    while(data.nb_of_philo)
    {
        pthread_join(philo[i].thread,NULL);
        i++;
        data.nb_of_philo--;
    }
}

void initialization(t_data *data,t_philo *philo)
{
    int i;
    int nb = 0;

    i = 0;
    while (nb < data->nb_of_philo)
        philo[nb++].leftfork = malloc(sizeof(pthread_mutex_t));
    while(i < data->nb_of_philo)
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
}

void thread_creat(t_data *data,t_philo *philo)
{
    int i;

    i   =   0;
    gettimeofday(&philo->ph_data->first_time,0);
    philo->ph_data->time = philo->ph_data->first_time.tv_usec;
    while(i < data->nb_of_philo)
    {
        pthread_create(&philo[i].thread,NULL,handler,&philo[i]);
        i++;
    }
}

int main(int ac,char **av)
{
    if(ac != 5 && ac != 6)
        return 0;
    t_data data;
    t_philo *philo;
    data.nb_of_philo = ft_atoi(av[1]);
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
        data.nb = ft_atoi(av[5]);
    philo = malloc(data.nb_of_philo * sizeof(t_philo));
    initialization(&data,philo);
    thread_creat(&data,philo);
    join_thread(data,philo);
    
}