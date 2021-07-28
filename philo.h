/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:35:02 by chicky            #+#    #+#             */
/*   Updated: 2021/07/27 18:13:40 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct  s_philo
{
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_times_philo_eat;
	int	last_meal;
	int	philo;
	pthread_mutex_t lock;
}              t_philo;

int	ft_atoi(const char *str);


int counter;



#endif