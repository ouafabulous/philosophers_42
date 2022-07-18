/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_stopper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 01:05:05 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/17 23:27:10 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
	if (!s1 || !s2)
		return (-1);
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return (*s1 - *s2);
	return (0);
}

int	is_any_p_dead(t_philo *philo)
{
	pthread_mutex_lock(&((philo->data->sdrei)[1]));
	if (philo->data->state)
	{
		pthread_mutex_unlock(&((philo->data->sdrei)[1]));
		return (1);
	}
	pthread_mutex_unlock(&((philo->data->sdrei)[1]));
	return (0);
}

int	there_is_blood(t_philo *philo, char *str)
{
	UINT	delay;

	if (is_any_p_dead(philo))
		return (2);
	if (philo->n_eaten)
		delay = get_timestamp(philo->lm_time);
	else
		delay = get_timestamp(philo->data->t_launch);
	if (!ft_strncmp(str, "is dead", 7) || delay >= philo->data->t_die)
	{
		pthread_mutex_lock(&((philo->data->sdrei)[1]));
		if (philo->data->state)
			return (pthread_mutex_unlock(&((philo->data->sdrei)[1])), 2);
		else
		{
			// printf("I entered here with this philo_v2: %d\n", philo->id);
			philo->data->state = 2;
			pthread_mutex_unlock(&((philo->data->sdrei)[1]));
			pthread_mutex_lock(&(philo->data->sdrei[0]));
			printf("%u %d %s\n", get_timestamp(philo->data->t_launch), philo->id, "is dead");
			pthread_mutex_unlock(&(philo->data->sdrei[0]));
			return (1);
		}
		pthread_mutex_unlock(&((philo->data->sdrei)[1]));
	}
	return (0);
}

int	all_eaten(t_philo *philo, int n_eat, int i)
{
	if (n_eat == -1)
		return (0);
	pthread_mutex_lock(&((philo->data->sdrei)[3]));
	if(philo->data->all_eaten == philo->data->n_phil && !i)
	{
		pthread_mutex_unlock(&((philo->data->sdrei)[3]));
		return (1);
	}
	pthread_mutex_unlock(&((philo->data->sdrei)[3]));
	return (0);
}

int	stop_simulation(t_philo *philo, int n_eat, char *str, int i)
{
	if (philo->data->n_phil > 1)
	{
		if (all_eaten(philo, n_eat, i) || there_is_blood(philo, str))
			return(1);
	}
	return (0);
}
