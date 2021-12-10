/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:29 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/10 01:19:37 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_pickup_and_eat(t_local_data *ldata, t_philo *philo)
{
	int	right;
	int	left;

	left = ldata->id;
	right = (ldata->id + 1) % philo->nbr_of_philos;
	pthread_mutex_lock(&philo->forks[left]);
	pthread_mutex_lock(&philo->forks[right]);
	ft_print_state(ldata, philo, Y "has taken a fork" RES);
	ft_print_state(ldata, philo, G "is eating" RES);
	ldata->count++;
	philo->count_eat[ldata->id] = ldata->count;
	mysleep(philo->time_to_eat);
	ldata->last_eat = current_timestamp();
	philo->last_meal[ldata->id] = ldata->last_eat;
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[right]);
}

void	ft_sleep_and_think(t_local_data *ldata, t_philo *philo)
{
	ft_print_state(ldata, philo, B "is sleeping" RES);
	mysleep(philo->time_to_sleep);
	ft_print_state(ldata, philo, M "is thinking" RES);
}

void	*trythis(void *data)
{
	t_philo			*philo;
	t_local_data	var;

	philo = (t_philo *)data;
	var.id = philo->idofphilo;
	philo->count_eat[var.id] = 0;
	/* argc should be added */ 
	// if (philo->nbr_times_philo_eat == 0)
	// 	return (NULL);
	var.count = 0;
	var.last_eat = current_timestamp();
	while (1)
	{
		ft_pickup_and_eat(&var, philo);
		ft_sleep_and_think(&var, philo);
	}
	return (NULL);
}

void	free_all(t_philo *philo)
{
	int	i;

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
int	ft_creat_threads(t_philo *philo)
{
	int i;
	int error;

	i = 0;
	while (i < philo->nbr_of_philos)
	{
		philo->idofphilo = i;
		error = pthread_create(&(philo->threads[i]),
				NULL,
				trythis, philo);
		if (error != 0)
			return (1);
		usleep(100);
		i++;
	}
	return (0);
}
int	main(int argc, char **argv)
{
	t_philo	*philo;
	//int		i;
	//int		error;

	philo = init_data(argc, argv);
	if (philo == NULL)
		return (1);
	//i = 0;
	philo->prog_start = current_timestamp();
	philo->threads = malloc (sizeof(pthread_t) * philo->nbr_of_philos);
	if (philo->threads == NULL)
		return (1);
	philo->death = 0;
	if (ft_creat_threads(philo) == 1)
		return (1);
	// while (i < philo->nbr_of_philos)
	// {
	// 	philo->idofphilo = i;
	// 	error = pthread_create(&(philo->threads[i]),
	// 			NULL,
	// 			trythis, philo);
	// 	if (error != 0)
	// 		return (1);
	// 	usleep(100);
	// 	i++;
	// }
	ft_supervisor(philo, argc);
	free_all(philo);
	return (0);
}
