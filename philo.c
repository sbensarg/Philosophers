/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chicky <chicky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:49:54 by chicky            #+#    #+#             */
/*   Updated: 2021/08/07 16:16:54 by chicky           ###   ########.fr       */
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

t_philo  init_data(int argc, char **argv)
{
    t_philo data;
   // t_mutex *mutex;
    int i;
    int error;

    i = 0;
    if (argc > 6 || argc < 5)
        printf("invalid args!!!");
    else
    {
        data.philo = malloc(sizeof(t_philo));
        data.philo->nbr_of_philos = ft_atoi(argv[1]);
        data.philo->time_to_die = ft_atoi(argv[2]);
        data.philo->time_to_eat = ft_atoi(argv[3]);
        data.philo->time_to_sleep = ft_atoi(argv[4]);
       // data.last_meal = 0;
        if (argc > 5)
            data.philo->nbr_times_philo_eat = ft_atoi(argv[5]);
		data.idofphilo = 0;
        data.prog_start = current_timestamp();
        // while(i < data.philo->nbr_of_philos)
        // {
            data.state = malloc(data.philo->nbr_of_philos + 1);
        //     i++;
        // }
        // i = 0;
        data.init_forks = (pthread_mutex_t *)malloc (sizeof(pthread_mutex_t) * data.philo->nbr_of_philos);
        while (i < data.philo->nbr_of_philos)
        {
            error = pthread_mutex_init(&(data.init_forks[i]), NULL);
            if (error != 0)
                printf("\nThread can't be created :[%s]",
                strerror(error));
        i++;
    }
        pthread_mutex_init(&data.print, NULL);
      //  pthread_mutex_init(&data.m_state, NULL);
       // pthread_mutex_init(&data.num_of_meals, NULL);
        // i = 0;
        // while (i < data.philo->nbr_of_philos)
        // {
        //     data.left_fork = i;
        //     data.right_fork = (i + 1) % data.philo->nbr_of_philos;
        //    i++;
        // }
    }
   
    return (data);
}
void ft_print_state(t_philo *philo, char *str)
{
    long long cur_time;
    cur_time = current_timestamp();
    pthread_mutex_lock(&philo->print);
    philo->idofphilo++;
    printf("%lld ms philosopher %d %s\n", (cur_time - philo->prog_start), philo->idofphilo, str);
    pthread_mutex_unlock(&philo->print);
}

void ft_pickup(t_philo *philo)
{
   // pthread_mutex_lock(&philo->m_state);
    int left_philo;
    int right_philo;

    left_philo = (philo->idofphilo - 1) % philo->philo->nbr_of_philos;
    right_philo = (philo->idofphilo + 1) % philo->philo->nbr_of_philos;
    philo->state[philo->idofphilo] = HUNGRY;
    ft_print_state(philo, "has taken a fork");
    if (philo->state[philo->idofphilo] == HUNGRY && philo->state[left_philo] != EATING && philo->state[right_philo] != EATING)
        philo->state[philo->idofphilo] = EATING;
    //pthread_mutex_unlock(&philo->m_state);
}

void ft_eat(t_philo *philo)
{
   // (i + 1) % data.philo->nbr_of_philos
    pthread_mutex_lock(philo->init_forks);
}
void* trythis(void *data)
{   
	t_philo *philo;
	long long cur_time;
	philo = (t_philo *)data;
	cur_time = current_timestamp();
 
 //   pthread_mutex_lock(&philo->lock);
	//philo->idofphilo++;
	
    //printf("%lld %d  has taken a fork\n", (cur_time - philo->prog_start), philo->idofphilo);
	
    
   // pthread_mutex_unlock(&philo->lock);
       ft_pickup(philo);
       ft_eat(philo);
       //ft_sleep();
       //ft_think();
  
    return NULL;
}

int main(int argc, char **argv)
{
    t_philo data;
    int i;
    int error;
    
    i = 0;
    
    data = init_data(argc, argv);
    pthread_t tid[data.philo->nbr_of_philos];
    
    // if (pthread_mutex_init(&data.lock, NULL) != 0) {
    //     printf("\n mutex init has failed\n");
    //     return 1;
    // }
    
    i = 0;
    while (i < data.philo->nbr_of_philos)
	{
        error = pthread_create(&(tid[i]),
                               NULL,
                               &trythis, &data);
        if (error != 0)
            printf("\nThread can't be created :[%s]",
                strerror(error));
        i++;
    }
	i = 0;
    while (i < data.philo->nbr_of_philos)
    {
       pthread_join(tid[i], NULL); 
       i++; 
    }
  //  pthread_mutex_destroy(&data.lock);
  
    return 0;

    
}