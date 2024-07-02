/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:43:43 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/01 18:11:46 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long time_of_ph(t_philo *philo)
{
    long time;

    pthread_mutex_lock(&philo->ph_data->mtx_to_print);
    time = get_time() - philo->ph_data->time;
    pthread_mutex_unlock(&philo->ph_data->mtx_to_print);
    return time;
}

void eat(t_philo *philo)
{
    pthread_mutex_lock(philo->leftfork);
    printf("%ld philo nb %d  has taken a leftfork \n",time_of_ph(philo),philo->id_of_philo);

    pthread_mutex_lock(philo->right_fork);   
    printf("%ld philo nb %d  has taken a right_fork \n",time_of_ph(philo), philo->id_of_philo);
    printf("%ld philo nb %d  is eating \n",time_of_ph(philo) , philo->id_of_philo);
    pthread_mutex_lock(&philo->ph_data->mtx_eat);
        philo->eat--;
    pthread_mutex_unlock(&philo->ph_data->mtx_eat);
    philo->status = 1;
    ft_usleep(philo->ph_data->time_to_eat);
    pthread_mutex_lock(&philo->ph_data->mtx_to_time);
        philo->old_time = get_time();
    pthread_mutex_unlock(&philo->ph_data->mtx_to_time);

    pthread_mutex_unlock(philo->leftfork);
    pthread_mutex_unlock(philo->right_fork); 
}

void sleeping(t_philo *philo)
{
    printf("%ld philo nb %d  is sleeping \n", time_of_ph(philo),philo->id_of_philo);
    ft_usleep(philo->ph_data->time_to_sleep);
}

void thinking(t_philo *philo)
{
	printf("%ld philo nb %d  is thinking \n", time_of_ph(philo),philo->id_of_philo);
}

void *handler(void *arg)
{
    t_philo *philo;
    philo = (t_philo *)arg;
    philo->eat = philo->ph_data->eat;
    philo->old_time = get_time();
    philo->status = 0;
    philo->fg = 0;
    if(philo->id_of_philo % 2)
        ft_usleep(philo->ph_data->time_to_eat - 10);
    while(1)
    {
        if (philo->ph_data->flag == 1)
            return (NULL);
        if (philo->fg == 1)
            return (philo->ph_data->flag1++,NULL);
        //printf("%d\n",philo->eat);
        eat(philo);
        sleeping(philo);
        thinking(philo);
    }
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
    pthread_join(philo[0].ph_data->tr, NULL);
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
	pthread_mutex_init(&philo[0].ph_data->mtx_to_time, NULL);
	pthread_mutex_init(&philo[0].ph_data->mtx_to_print, NULL);
	pthread_mutex_init(&philo[0].ph_data->mtx_eat, NULL);
    pthread_mutex_init(&philo[0].ph_data->mtx_flag, NULL);
}

void *tr(void *arg)
{
    t_philo *philo;
    int i;

    i     = 0;
    philo = arg;
    ft_usleep(philo->ph_data->time_to_die - 10);
    while(1)
    {
        if (i == philo->ph_data->nb_of_philo)
            i = 0;
        if(philo->ph_data->flag1 >= philo->ph_data->nb_of_philo)
            return NULL ;
        pthread_mutex_lock(&philo->ph_data->mtx_to_time);
        
        if (get_time() - philo[i].old_time > philo[i].ph_data->time_to_die && philo->status != 1)
        {
            printf("%ld philo nb %d is died\n",time_of_ph(&philo[i]), philo[i].id_of_philo);
            philo->ph_data->flag = 1;
            pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
            return NULL;
        }
        pthread_mutex_unlock(&philo->ph_data->mtx_to_time);
        pthread_mutex_lock(&philo->ph_data->mtx_eat);
        if (philo[i].eat < 0)
            philo[i].fg = 1;
        pthread_mutex_unlock(&philo->ph_data->mtx_eat);
        i++;
    }
    return NULL;
}

void thread_creat(t_data *data,t_philo *philo)
{
    int i;

    i   =   0;
    data->time = get_time();
    data->flag = 0;
    data->flag1 = 0;
    while(i < data->nb_of_philo)
    {
        pthread_create(&philo[i].thread,NULL,handler,&philo[i]);
        i++;
    }
    pthread_create(&data->tr,NULL,tr,philo);
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
    data.flag1 = 0;
    if(ac == 6)
    {
        data.eat = ft_atoi(av[5]);
        data.flag1 = 1;
    }
    philo = malloc(data.nb_of_philo * sizeof(t_philo));
    initialization(&data,philo);
    thread_creat(&data,philo);
    join_thread(data,philo);
    
}