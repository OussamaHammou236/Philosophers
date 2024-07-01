/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:09 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/01 18:03:38 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHER_H
# define PHILOSOPHER_H


#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

int	ft_atoi(const char *str);
void ft_error(char *str);
size_t	ft_strlen(const char *str);
long    get_time();
void    ft_usleep(long time);

typedef struct s_data
{
    int nb_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int eat;
    int flag;
    struct timeval first_time;
    pthread_mutex_t mtx_to_time;
    pthread_mutex_t mtx_eat;
    pthread_mutex_t mtx_to_print;
    pthread_mutex_t mtx_flag;
    pthread_t tr;
    long int time;
    long int nb;
    int flag1;
    int i;
} t_data;

typedef struct s_philo
{
    pthread_t thread;
    pthread_mutex_t *leftfork;
    pthread_mutex_t *right_fork;
    t_data *ph_data;
    int id_of_philo;
    long int time_of_philo;
    long int old_time;
    int eat;
} t_philo;


#endif