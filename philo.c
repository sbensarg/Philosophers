/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:29 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/08 20:22:03 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_mutex(t_philo	*data)
{
	int		error;
	int		i;

	i = 0;
	data->forks = (pthread_mutex_t *)malloc (sizeof(pthread_mutex_t) * data->nbr_of_philos);
	while (i < data->nbr_of_philos)
	{
		error = pthread_mutex_init(&(data->forks[i]), NULL);
		if (error != 0)
			printf("\n mutex can't be initialized :[%s]",
			strerror(error));
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->num_of_meals, NULL);
	return(data);
}

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*data;
	int		j;
	
	j = -1;
	data = malloc(sizeof(t_philo));
	if (argc > 6 || argc < 5)
		printf("invalid args!!!");
	else
	{
		data->nbr_of_philos = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat =  ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argc > 5)
			data->nbr_times_philo_eat = ft_atoi(argv[5]);
		data = init_mutex(data);
		data->count_eat = malloc (sizeof(int) * data->nbr_of_philos);
		data->last_meal = malloc(sizeof(long long) * data->nbr_of_philos);
		while (++j < data->nbr_of_philos)
			data->last_meal[j] = current_timestamp();
	}
	return (data);
}

void	ft_pickup_and_eat(t_local_data *ldata, t_philo *philo)
{
	int right;
	int	left;

	left = ldata->id;
	right = (ldata->id + 1) % philo->nbr_of_philos;
	pthread_mutex_lock(&philo->forks[left]);
	pthread_mutex_lock(&philo->forks[right]);
    ft_print_state(ldata, philo, ANSI_COLOR_YELLOW "has taken a fork"  ANSI_COLOR_RESET);
	ft_print_state(ldata, philo, ANSI_COLOR_GREEN "is eating" ANSI_COLOR_RESET);
	pthread_mutex_lock(&philo->num_of_meals);
	ldata->count++;
	philo->count_eat[ldata->id] = ldata->count;
	pthread_mutex_unlock(&philo->num_of_meals);
	ldata->last_eat = current_timestamp();
	philo->last_meal[ldata->id] = ldata->last_eat;
	mysleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[right]);
}

void	ft_sleep_and_think(t_local_data *ldata, t_philo *philo)
{
	ft_print_state(ldata, philo, ANSI_COLOR_BLUE "is sleeping" ANSI_COLOR_RESET);
	mysleep(philo->time_to_sleep);
	ft_print_state(ldata, philo, ANSI_COLOR_MAGENTA "is thinking" ANSI_COLOR_RESET);
}

void*	trythis(void *data)
{   
	t_philo *philo;
	t_local_data *var;

	philo = (t_philo *)data;
	var = malloc(sizeof(t_local_data));
	var->id = philo->idofphilo;
	var->count = 0;
	var->last_eat = current_timestamp();
	while (1)
	{
		ft_pickup_and_eat(var, philo);
		ft_sleep_and_think(var, philo);
	}
    return NULL;
}
void	check_death(t_philo *philo)
{
	int j;
	
	j = 0;
	while (j < philo->nbr_of_philos)
	{
		if (current_timestamp() - philo->last_meal[j] > philo->time_to_die)
		{
			pthread_mutex_lock(&philo->print);
			printf("%lld ms philosopher %d died\n", (current_timestamp() - philo->prog_start), philo->idofphilo + 1);
			philo->death = 1;
			break ;
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
	while(i < philo->nbr_of_philos)
	{
		if (philo->count_eat[i] == philo->nbr_times_philo_eat)
			var += 1;
		i++;
	}
	return (var);
}

void	ft_supervisor(t_philo *philo)
{
	int var;

	var = 0;
	while (1)
	{
		var = check_if_all_philos_eat(philo);
		if (var == philo->nbr_of_philos)
			break ;
		check_death(philo);
		if (philo->death == 1)
			break ;
	}
}


int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	int		error;

	philo = init_data(argc, argv);
	i = 0;
	philo->prog_start = current_timestamp();
	philo->threads = (pthread_t *)malloc (sizeof(pthread_t) * philo->nbr_of_philos);
    philo->death = 0;
	while (i < philo->nbr_of_philos)
	{
		philo->idofphilo = i;
		error = pthread_create(&(philo->threads[i]),
					NULL,
						trythis, philo);
		if (error != 0)
		printf("\nthread can't be created :[%s]",
		strerror(error));
		usleep(100);
		i++;
	}
	ft_supervisor(philo);
	pthread_mutex_destroy(philo->forks);
	pthread_mutex_destroy(&philo->num_of_meals);
	pthread_mutex_destroy(&philo->print);
}