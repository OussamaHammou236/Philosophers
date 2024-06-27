/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:10:12 by ohammou-          #+#    #+#             */
/*   Updated: 2024/06/27 18:01:04 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    ft_usleep(long time)
{
    long    start;

    start = get_time();
    while ((get_time() - start) < time)
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
// 1s -> 1000ms
// 1ms -> 1000us