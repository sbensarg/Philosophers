/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:42 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/10 00:19:01 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

# define R	"\x1b[31m"
# define G	"\x1b[32m"
# define Y	"\x1b[33m"
# define B	"\x1b[34m"
# define M	"\x1b[35m"
# define C	"\x1b[36m"
# define RES	"\x1b[0m"

typedef struct s_philo
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
	int				death;
}					t_philo;

typedef struct s_local_data
{
	int				id;
	int				count;
	long long		last_eat;
}					t_local_data;

int			ft_atoi(const char *str);
long long	current_timestamp(void);
void		mysleep(long long time);
void		ft_print_state(t_local_data *ldata, t_philo *philo, char *str);
int			init_args(t_philo *data, int argc, char **argv);
int			init_mutex(t_philo	*data);
t_philo		*init_data(int argc, char **argv);
void		check_death(t_philo *philo, int argc);
int			check_if_all_philos_eat(t_philo *philo);
void		ft_supervisor(t_philo *philo, int argc);
void		free_all(t_philo *philo);

#endif