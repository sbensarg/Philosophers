/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:42 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/11 19:56:27 by sbensarg         ###   ########.fr       */
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

#define HUNGRY 0
#define EATING 1
#define SLEEPING 2
#define THINKING 3
#define DIED 4

typedef struct	s_common_data
{
    int				nbr_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_times_philo_eat;
	pthread_mutex_t	*init_forks;
	pthread_mutex_t	print;
	int				count_eat;
  	pthread_mutex_t	num_of_meals;
	int				*state;
	pthread_mutex_t	m_state;
}					t_common_data;

typedef struct	s_philo
{
	t_common_data	*data;
    int				idofphilo;
	pthread_t		thread_id;
    int				last_meal;
    int				prog_start;
}					t_philo;


int	ft_atoi(const char *str);

#endif