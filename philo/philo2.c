/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:47:32 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/10 01:15:55 by sbensarg         ###   ########.fr       */
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
	pthread_mutex_init(&(data->print), NULL);
	return (0);
}

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*data;
	int		j;

	j = -1;
	data = malloc(sizeof(t_philo));
	if (data == NULL)
		return (NULL);
	if (argc > 6 || argc < 5)
		return (NULL);
	else
	{
		if (init_args(data, argc, argv) == 1)
			return (NULL);
		if (init_mutex(data) == 1)
			return (NULL);
		data->count_eat = malloc (sizeof(int) * data->nbr_of_philos);
		if (data->count_eat == NULL)
			return (NULL);
		data->last_meal = malloc(sizeof(long long) * data->nbr_of_philos);
		if (data->last_meal == NULL)
			return (NULL);
		while (++j < data->nbr_of_philos)
			data->last_meal[j] = current_timestamp();
	}
	return (data);
}

void	check_death(t_philo *philo, int argc)
{
	int	j;

	j = 0;
	while (j < philo->nbr_of_philos)
	{
		if ((argc == 6 && philo->count_eat[j] < philo->nbr_times_philo_eat) || argc == 5)
		{
			if (current_timestamp() - philo->last_meal[j] >= philo->time_to_die)
			{
				pthread_mutex_lock(&philo->print);
				printf("%lld ms philosopher %d died\n",
					(current_timestamp() - philo->prog_start), j + 1);
				philo->death = 1;
				break ;
			}
		}
		j++;
	}
}

int	check_if_all_philos_eat(t_philo *philo)
{
	int	var;
	int	i;

	i = 0;
	var = 0;
	while (i < philo->nbr_of_philos)
	{
		if (philo->count_eat[i] == philo->nbr_times_philo_eat)
			var += 1;
		i++;
	}
	return (var);
}

void	ft_supervisor(t_philo *philo, int argc)
{
	int	var;

	var = 0;
	while (1)
	{
		if (argc == 6)
		{
			var = check_if_all_philos_eat(philo);
			if (var == philo->nbr_of_philos)
				break ;
		}
		check_death(philo, argc);
		if (philo->death == 1)
			break ;
	}
}
