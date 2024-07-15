/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:02 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/26 18:19:55 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
int c = 0;

void    *handler(void *arg)
{
    int i = 0;
    t_data *data = arg;
    while (i < 200)
    {
    	pthread_mutex_lock(&data->status);
	    if (data->flag == 1)
	    {
		    pthread_mutex_unlock(&data->status);
		    return NULL;
	    }
        printf("%d\n",i);
        if(i == 100)
            data->flag  = 1;
        i++;
	    pthread_mutex_unlock(&data->status);
        usleep(500);
    }
}
 

int main()
{
    pthread_t thread;
    pthread_t thread2;
    pthread_t thread3;
    pthread_t thread4;
    pthread_t thread5;
    pthread_t thread1;
    pthread_mutex_t mutex;
    t_data data;
    data.flag = 0;
    gettimeofday(&data.first_time,0);
    //printf("%ld'\n",data.first_time.tv_usec);
    pthread_mutex_init(&data.status, NULL);
    pthread_create(&thread, NULL, handler, &data);
    pthread_create(&thread2, NULL, handler, &data);
    pthread_create(&thread3, NULL, handler, &data);
    pthread_create(&thread4, NULL, handler, &data);
    pthread_create(&thread5, NULL, handler, &data);
    pthread_create(&thread1, NULL, handler, &data);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL); 
    pthread_join(thread3, NULL); 
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL); 
    pthread_join(thread1, NULL);
    
}