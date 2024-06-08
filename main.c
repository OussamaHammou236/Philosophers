/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:02 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/08 20:39:39 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
int c = 0;
void *handler(void *ar)
{
    pthread_mutex_lock(ar);
    printf("1\n");
    sleep(2);
    printf("2\n");
    pthread_mutex_unlock(ar);
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_t thread1;
    pthread_mutex_t mutex;
    pthread_create(&thread, NULL, handler, &mutex);
    pthread_create(&thread1, NULL, handler, &mutex);
    pthread_mutex_init(&mutex, NULL);
    pthread_join(thread, NULL);
    pthread_join(thread1, NULL);
}