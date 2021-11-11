/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:35:02 by chicky            #+#    #+#             */
/*   Updated: 2021/08/07 15:44:19 by chicky           ###   ########.fr       */
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

#define HUNGRY 0
#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DIED 4

typedef struct  s_common_data
{
    int nbr_of_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nbr_times_philo_eat;
}              t_common_data;

typedef struct s_philo
{
    int idofphilo;
    int left_philo;
    int right_philo;
    int	last_meal;
    int right_fork;
    int left_fork;
    int prog_start;
    int *state;
    pthread_mutex_t *init_forks;
    pthread_mutex_t m_state;
    pthread_mutex_t print;
    pthread_mutex_t num_of_meals;
    //pthread_mutex_t lock;
    t_common_data *philo;
}              t_philo;

typedef struct s_mutex
{
    pthread_mutex_t *init_forks;
    pthread_mutex_t state;
    pthread_mutex_t print;
    pthread_mutex_t num_of_meals;
}              t_mutex;


int	ft_atoi(const char *str);






#endif