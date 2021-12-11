/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:50:28 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/11 18:19:53 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_philo	*data)
{
	int		error;
	int		i;

	i = 0;
	data->forks = malloc (sizeof(pthread_mutex_t) * data->nbr_of_philos);
	if (data->forks == NULL)
		return (1);
	while (i < data->nbr_of_philos)
	{
		error = pthread_mutex_init(&(data->forks[i]), NULL);
		if (error != 0)
			return (1);
		i++;
	}
	error = pthread_mutex_init(&(data->print), NULL);
	if (error != 0)
		return (1);
	return (0);
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

int	init_utils(t_philo *data)
{
	int		j;

	j = -1;
	data->count_eat = malloc (sizeof(int) * data->nbr_of_philos);
	if (data->count_eat == NULL)
		return (1);
	data->last_meal = malloc(sizeof(long long) * data->nbr_of_philos);
	if (data->last_meal == NULL)
		return (1);
	while (++j < data->nbr_of_philos)
		data->last_meal[j] = current_timestamp();
	return (0);
}

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*data;

	data = malloc(sizeof(t_philo));
	if (data == NULL)
		return (NULL);
	data->ac = argc;
	if (argc > 6 || argc < 5)
		return (NULL);
	else
	{
		if (init_args(data, argc, argv) == 1)
			return (NULL);
		if (init_mutex(data) == 1)
			return (NULL);
		if (init_utils(data) == 1)
			return (NULL);
	}
	return (data);
}
