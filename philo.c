/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:29 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/04 21:05:44 by chicky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_timestamp()
{
	struct		timeval te; 
	long long	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec) * 1000 + (te.tv_usec) / 1000;
	return milliseconds;
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
		pthread_mutex_init(&data->num_of_meals, NULL);
	}
	return (data);
}

void ft_print_state(t_philo *philo, char *str)
{
    long long cur_time;
    cur_time = current_timestamp();
    pthread_mutex_lock(&philo->print);
    printf("%lld ms philosopher %d %s\n", (cur_time - philo->prog_start), philo->idofphilo + 1, str);
    pthread_mutex_unlock(&philo->print);
}

void ft_pickup(t_philo *philo)
{
	int right;
	int	left;
	
	left = philo->idofphilo;
	right = (philo->idofphilo + 1) % philo->nbr_of_philos;
	pthread_mutex_lock(&philo->forks[left]);
	pthread_mutex_lock(&philo->forks[right]);
    ft_print_state(philo, ANSI_COLOR_YELLOW "has taken a fork"  ANSI_COLOR_RESET);
	pthread_mutex_unlock(&philo->forks[left]);
	pthread_mutex_unlock(&philo->forks[right]);
	
}

void ft_eat(t_philo *philo)
{
	ft_print_state(philo, ANSI_COLOR_GREEN "is eating" ANSI_COLOR_RESET);
	usleep(philo->time_to_eat * 1000);	
}


void*	trythis(void *data)
{   
	t_philo *philo;
	
	philo = (t_philo *)data;
	
	while (1)
	{
		ft_pickup(philo);
		ft_eat(philo);
	}
    return NULL;
}

int	main(int argc, char **argv)
{
	t_philo *philo;
	int		i;
	int		error;

	philo = init_data(argc, argv);
	i = 0;
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
		usleep(2000);
        i++;
    }
	i = 0;
    while (i < philo->nbr_of_philos)
    {
       pthread_join(philo->threads[i], NULL); 
       i++; 
    }
	  pthread_mutex_destroy(philo->forks);
	  pthread_mutex_destroy(&philo->num_of_meals);
	  pthread_mutex_destroy(&philo->print);
	  
}