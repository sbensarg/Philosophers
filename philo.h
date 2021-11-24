/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:42 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/12 20:03:32 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct	s_philo
{
    int				idofphilo;
	pthread_t		*threads;
    int				last_meal;
    int				prog_start;
	int				nbr_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_times_philo_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				count_eat;
  	pthread_mutex_t	num_of_meals;
	long long		cur_time;
}					t_philo;


int	ft_atoi(const char *str);

#endif