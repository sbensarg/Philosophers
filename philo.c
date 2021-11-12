/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:42:29 by sbensarg          #+#    #+#             */
/*   Updated: 2021/11/12 01:38:08 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_timestamp()
{
	struct		timeval te; 
	long long	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec) * 1000 + (te.tv_usec) / 1000;
	return (milliseconds);
}

t_common_data	*init_data(int argc, char **argv)
{
	t_common_data	*data;
	int				i;
	int				error;
	
	i = 0;
	data = malloc(sizeof(t_common_data));
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
		data->init_forks = (pthread_mutex_t *)malloc (sizeof(pthread_mutex_t) * data->nbr_of_philos);
		while (i < data->nbr_of_philos)
		{
			error = pthread_mutex_init(&(data->init_forks[i]), NULL);
            if (error != 0)
                printf("\n Mutex can't be initialized :[%s]",
                strerror(error));
			i++;
		}
		pthread_mutex_init(&data->print, NULL);
		data->count_eat = 0;
		pthread_mutex_init(&data->num_of_meals, NULL);
		i = 0;
		while(i < data->nbr_of_philos)
		{
			data->state = malloc(data->nbr_of_philos + 1);
			i++;
		}
		pthread_mutex_init(&data->m_state, NULL);
	}

	return (data);
}

void ft_print_state(t_philo *philo, char *str)
{
    long long cur_time;
    cur_time = current_timestamp();
    pthread_mutex_lock(&philo->data->print);
    printf("%lld ms philosopher %d %s\n", (cur_time - philo->prog_start), philo->idofphilo, str);
    pthread_mutex_unlock(&philo->data->print);
}

// void	ft_eat(t_philo *philo)
// {
	
// }

void ft_pickup(t_philo *philo)
{
    int left_philo;
    int right_philo;
	
	left_philo = philo->idofphilo - 1;
	right_philo = philo->idofphilo + 1;
	pthread_mutex_lock(&philo->data->init_forks[left_philo]);
    pthread_mutex_lock(&philo->data->init_forks[right_philo]);
	pthread_mutex_lock(&philo->data->m_state);
    philo->data->state[philo->idofphilo] = HUNGRY;
    ft_print_state(philo, "has taken a fork");
    if (philo->data->state[philo->idofphilo] == HUNGRY && philo->data->state[left_philo] != EATING && philo->data->state[right_philo] != EATING)
       philo->data->state[philo->idofphilo] = EATING;
    pthread_mutex_unlock(&philo->data->m_state);
	pthread_mutex_unlock(&philo->data->init_forks[left_philo]);
	pthread_mutex_unlock(&philo->data->init_forks[right_philo]);
}

void*	trythis(void *philo)
{   
	t_philo	*philos;

	philos = (t_philo *)philo;
	philos->prog_start = current_timestamp();
	
	ft_pickup(philos);
	//ft_eat(philos);
	
    return NULL;
}

int main (int argc, char **argv)
{
	t_common_data	*data;
	t_philo			*philos;
	int				i;
	int				error;
	
	i = 0;
	data = init_data(argc, argv);
	philos = malloc(sizeof(t_philo) * data->nbr_of_philos);
	while (i <= data->nbr_of_philos)
	{
		philos[i].idofphilo = i + 1;
		philos->data = data;
		i++;
	}
	i = 0;
	while (i < data->nbr_of_philos)
	{
		
		error = pthread_create(&philos[i].thread_id, NULL, &trythis, &philos[i]);
		if (error != 0)
		 	printf("\nThread can't be created :[%s]",
		 	strerror(error));
		i++;
	}
	
	i = 0;
    while (i < data->nbr_of_philos)
    {
       pthread_join(philos[i].thread_id, NULL); 
       i++;    
    }

	return(0);
	
}