/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/10 20:21:48 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void *handler(void *arg)
{
    printf("aaa\n");
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

void initialization(t_data data,t_philo *philo)
{
    int i;
    int nb;

    nb = 1;
    i = 0;
    while(data.nb_of_philo)
    {
        pthread_create(&philo[i].thread,NULL,handler,NULL);
        pthread_mutex_init(&philo[i].mutex, NULL);
        philo[i].id_of_philo = nb;
        nb++;
        i++;
        data.nb_of_philo--;
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
    initialization(data,philo);
    join_thread(data,philo);
    
}