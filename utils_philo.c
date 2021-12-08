/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:50:36 by chicky            #+#    #+#             */
/*   Updated: 2021/12/08 20:01:33 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	current_timestamp(void)
{
	struct		timeval te; 
	long long	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec) * 1000 + (te.tv_usec) / 1000;
	return milliseconds;
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
	printf("%lld ms philosopher %d %s\n", (cur_time - philo->prog_start), ldata->id + 1, str);
	pthread_mutex_unlock(&philo->print);
}