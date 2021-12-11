/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:50:36 by chicky            #+#    #+#             */
/*   Updated: 2021/12/11 18:41:09 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	a;
	int		s;

	i = 0;
	a = 0;
	s = 1;
	while ((str[i] >= 8 && str[i] <= 13) || str[i] == 32)
	{
		if (str[i] == 27)
			return (0);
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
		a = a * 10 + str[i++] - 48;
	return (a * s);
}

long long	current_timestamp(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec) * 1000 + (te.tv_usec) / 1000;
	return (milliseconds);
}

void	mysleep(long long time)
{
	long long	cur_time;

	cur_time = current_timestamp();
	usleep((time * 1000) * 0.8);
	while (current_timestamp() - cur_time < time)
		continue ;
}

void	ft_print_state(t_local_data *ldata, t_philo *philo, char *str)
{
	long long	cur_time;

	cur_time = current_timestamp();
	pthread_mutex_lock(&philo->print);
	printf("%lld ms philosopher %d %s\n", cur_time, ldata->id + 1, str);
	pthread_mutex_unlock(&philo->print);
}

void	free_all(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_of_philos)
	{
		pthread_detach(philo->threads[i]);
		i++;
	}
	i = 0;
	while (i < philo->nbr_of_philos)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->print);
	free(philo->forks);
	free(philo->threads);
	free(philo->count_eat);
	free(philo->last_meal);
	free(philo);
}
