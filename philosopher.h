/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:09 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/25 19:06:20 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

int	ft_atoi(const char *str);
void ft_error(char *str);
size_t	ft_strlen(const char *str);

typedef struct s_data
{
    int nb_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb;
    int i;
} t_data;

typedef struct s_philo
{
    pthread_t thread;
    pthread_mutex_t *leftfork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t mtx;
    t_data *ph_data;
    int id_of_philo;
    
} t_philo;


#endif