/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohammou- <ohammou-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:09 by ohammou-          #+#    #+#             */
/*   Updated: 2024/07/18 11:19:57 by ohammou-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat;
	int				flag;
	struct timeval	first_time;
	pthread_mutex_t	mtx_to_time;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_to_print;
	pthread_mutex_t	mtx_flag;
	pthread_mutex_t	status;
	pthread_t		tr;
	long int		time;
	long int		nb;
	int				flag1;
	int				i;
	int				flag2;
}					t_data;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	*leftfork;
	pthread_mutex_t	*right_fork;
	t_data			*ph_data;
	int				id_of_philo;
	long int		time_of_philo;
	long int		old_time;
	int				eat;
	int				fg;
	int				status;
}					t_philo;

int					ft_atoi(const char *str);
int					ft_error(char *str);
size_t				ft_strlen(const char *str);
long				get_time(void);
void				ft_usleep(long time, t_philo *philo);
void				join_thread(t_data data, t_philo *philo);
void				initialization(t_data *data, t_philo *philo);
void				thread_creat(t_data *data, t_philo *philo);
void				*handler(void *arg);
void				*tr(void *arg);
void				eat(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);
long				time_of_ph(t_philo *philo);
void				ft_printf(long time, t_philo *philo, int flag);
void				initialization_philo(t_philo *philo);

#endif