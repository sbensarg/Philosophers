/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:29 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/07 20:46:57 by sbensarg         ###   ########.fr       */
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

t_philo	*init_data(int argc, char **argv)
{
	t_philo	*data;
	int		i;
	int		error;
	
	i = 0;
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
		data->count_eat = 0;
		data->last_meal = 0;
		pthread_mutex_init(&data->num_of_meals, NULL);
		data->count_eat = malloc (sizeof(int) * data->nbr_of_philos);
	}
	return (data);
}

void	ft_print_state(t_local_data *ldata, t_philo *philo, char *str)
{
	long long	cur_time;

	cur_time = current_timestamp();
	pthread_mutex_lock(&philo->print);
	printf("%lld ms philosopher %d %s\n", (cur_time - philo->prog_start), ldata->id + 1, str);
	pthread_mutex_unlock(&philo->print);
}

void	ft_pickup_and_eat(t_local_data *ldata, t_philo *philo)
{
	int right;
	int	left;
	int i;

	i = 0;
	left = ldata->id;
	right = (ldata->id + 1) % philo->nbr_of_philos;
	pthread_mutex_lock(&philo->forks[left]);
	pthread_mutex_lock(&philo->forks[right]);
	if (current_timestamp() - ldata->last_eat >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->print);
		printf("%lld ms philosopher %d died\n", (current_timestamp() - philo->prog_start), ldata->id + 1);
		philo->death = 1;
	}
    ft_print_state(ldata, philo, ANSI_COLOR_YELLOW "has taken a fork"  ANSI_COLOR_RESET);
	ft_print_state(ldata, philo, ANSI_COLOR_GREEN "is eating" ANSI_COLOR_RESET);
	pthread_mutex_lock(&philo->num_of_meals);
	ldata->count++;
	philo->count_eat[ldata->id] = ldata->count;
	pthread_mutex_unlock(&philo->num_of_meals);
	ldata->last_eat = current_timestamp();
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
	long long	cur_time;

	cur_time = current_timestamp();
	philo = (t_philo *)data;
	var = malloc(sizeof(t_local_data));
	philo->last_meal =current_timestamp();
	var->id = philo->idofphilo;
	var->count = 0;
	var->last_eat = current_timestamp();
	while (1)
	{
		if (philo->death == 1)
			break ;
		usleep(10);
		ft_pickup_and_eat(var, philo);
		ft_sleep_and_think(var, philo);
	}
    return NULL;
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	int		i;
	int		error;
	int		var;

	philo = init_data(argc, argv);
	i = 0;
	var = 0;
	philo->prog_start = current_timestamp();
	philo->threads = (pthread_t *)malloc (sizeof(pthread_t) * philo->nbr_of_philos);
    while (i < philo->nbr_of_philos)
	{
		philo->idofphilo = i;
		error = pthread_create(&(philo->threads[i]),
					NULL,
						trythis, philo);
		if (error != 0)
		printf("\nthread can't be created :[%s]",
		strerror(error));
		usleep(10);
		i++;
	}
	i = 0;
	while (1)
	{
		i = 0;
		var = 0;
		if (philo->death == 1)
			break ;
		while(i < philo->nbr_of_philos)
		{
			if (philo->count_eat[i] == philo->nbr_times_philo_eat)
				var += 1;
			else
				var += 0;
			i++;
		}
		if (var == philo->nbr_of_philos)
			break ;
	}
	
	// i = 0;
    // while (i < philo->nbr_of_philos)
    // {
    //    pthread_join(philo->threads[i], NULL); 
    //    i++; 
    // }
	pthread_mutex_destroy(philo->forks);
	pthread_mutex_destroy(&philo->num_of_meals);
	pthread_mutex_destroy(&philo->print);
}