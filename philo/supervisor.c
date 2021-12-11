/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 22:47:32 by sbensarg          #+#    #+#             */
/*   Updated: 2021/12/11 16:01:04 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_philo *philo, int argc)
{
	int	j;

	j = 0;
	while (j < philo->nbr_of_philos)
	{
		if ((argc == 6 && philo->count_eat[j] < philo->nbr_times_philo_eat)
			|| argc == 5)
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
