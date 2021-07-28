/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:49:54 by chicky            #+#    #+#             */
/*   Updated: 2021/07/28 20:23:04 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_philo  init_data(int argc, char **argv)
{
    t_philo data;
    if (argc > 6 || argc < 5)
        printf("invalid args!!!");
    else
    {
        data.nbr_of_philos = ft_atoi(argv[1]);
        data.time_to_die = ft_atoi(argv[2]);
        data.time_to_eat = ft_atoi(argv[3]);
        data.time_to_sleep = ft_atoi(argv[4]);
        data.last_meal = 0;
        if (argc > 5)
            data.nbr_times_philo_eat = ft_atoi(argv[5]);
		data.idofphilo = 0;
    }
    return (data);
}

long long current_timestamp()
{
	struct		timeval te; 
	long long	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = (te.tv_sec) * 1000 + (te.tv_usec) / 1000;
	return milliseconds;
}

void* trythis(void *data)
{   
	t_philo *philo;
	long long cur_time;
	philo = (t_philo *)data;
	cur_time = current_timestamp();
 
    pthread_mutex_lock(&philo->lock);
	philo->idofphilo++;
	
    printf("%lld %d  has taken a fork\n",  cur_time, philo->idofphilo);
	
	
    // if (philo->time_to_die || philo->last_meal == 0)
    //     printf("%d %ld died\n", philo->nbr_of_philos,  current_time.tv_usec);
    
    pthread_mutex_unlock(&philo->lock);
  
    return NULL;
}

int main(int argc, char **argv)
{
    t_philo data;
    
    data = init_data(argc, argv);
    pthread_t tid[data.nbr_of_philos];
    
    int i = 0;
    int error;
  
    if (pthread_mutex_init(&data.lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }
  
    while (i < data.nbr_of_philos)
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
    while (i < data.nbr_of_philos)
    {
       pthread_join(tid[i], NULL); 
       i++; 
    }
    pthread_mutex_destroy(&data.lock);
  
    return 0;

    
}