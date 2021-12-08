/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:42 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/08 20:01:51 by chicky           ###   ########.fr       */
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

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct	s_philo
{
	int				idofphilo;
	pthread_t		*threads;
    long long		*last_meal;
    long			prog_start;
	int				nbr_of_philos;
    int				time_to_die;
    int				time_to_eat;
    int				time_to_sleep;
    int				nbr_times_philo_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	int				*count_eat;
  	pthread_mutex_t	num_of_meals;
	int				death;
}					t_philo;

typedef struct	s_local_data
{
    int				id;
	int				count;
	long long		last_eat;
}					t_local_data;

int			ft_atoi(const char *str);
long long	current_timestamp(void);
void		mysleep(long long time);
void	ft_print_state(t_local_data *ldata, t_philo *philo, char *str);

#endif