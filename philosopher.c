/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/09 20:40:50 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void initialization(t_data data,t_philo *philo)
{
    while(data.nb_of_philo)
    {
        
    }
}

int main(int ac,char **av)
{
    if(ac != 5 && ac != 6)
        return 0;
    t_data data;
    t_philo *philo;
    data.nb_of_philo = ft_atoi(av[1]);
    philo = malloc(data.nb_of_philo * sizeof(t_philo));
    data.time_to_die = ft_atoi(av[2]);
    data.time_to_eat = ft_atoi(av[3]);
    data.time_to_sleep = ft_atoi(av[4]);
    if(ac == 6)
        data.nb = ft_atoi(av[5]);
    initialization(data,philo);
    
}