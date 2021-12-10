/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:50:36 by chicky            #+#    #+#             */
/*   Updated: 2021/12/10 01:17:59 by sbensarg         ###   ########.fr       */
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
	printf("%lld ms philosopher %d %s\n",
		(cur_time - philo->prog_start), ldata->id + 1, str);
	pthread_mutex_unlock(&philo->print);
}

int	init_args(t_philo *data, int argc, char **argv)
{
	data->nbr_times_philo_eat = -1;
	data->nbr_of_philos = ft_atoi(argv[1]);
	if (data->nbr_of_philos > 200 || data->nbr_of_philos <= 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die < 60)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat < 60)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep < 60)
		return (1);
	if (argc > 5)
	{
		data->nbr_times_philo_eat = ft_atoi(argv[5]);
		if (data->nbr_times_philo_eat < 0)
			return (1);
	}
	return (0);
}
