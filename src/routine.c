/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:10:55 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 18:26:48 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*handle_one(t_philo *philo)
{
	if (!philo->data->t_die
		|| get_timestamp(philo->data->t_launch) >= philo->data->t_die)
		get_message(philo, "died", 0);
	else
	{
		get_message(philo, "has taken a fork", 0);
		usleep((philo->data->t_die
				- get_timestamp(philo->data->t_launch)) * 1000);
		get_message(philo, "died", 0);
	}
	return (NULL);
}

int	think(t_philo *philo)
{
	philo->thought = 1;
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&((philo->data->sdrei)[4]));
	if (philo->data->i && (philo->id % 2))
	{
		if (think_1(philo))
			return (1);
	}
	else
	{
		if (think_2(philo))
			return (1);
	}
	while (philo->data->mut[philo->id - 1].__data.__lock
		&& philo->data->mut[philo->next->id - 1].__data.__lock)
	{
		if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
			return (1);
		usleep(10);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	philo->thought = 0;
	if (philo->id % 2)
	{
		if (eat_odd(philo))
			return (1);
	}
	else if (eat_even(philo))
		return (1);
	return (0);
}

int	my_sleep(t_philo *philo)
{
	UINT	diff;

	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
	{
		return (1);
	}
	diff = philo->data->t_die - get_timestamp(philo->lm_time);
	if (diff <= philo->data->t_sleep)
	{
		if (get_message(philo, "is sleeping", 0))
			return (1);
		usleep(diff * 1000 - 20);
		get_message(philo, "is dead", 0);
		return (1);
	}
	else
	{
		if (get_message(philo, "is sleeping", 0))
			return (1);
		usleep(philo->data->t_sleep * 1000 - 10);
	}
	return (0);
}

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->data->n_phil == 1)
		return (handle_one(philo), NULL);
	pthread_mutex_lock(&((philo->data->sdrei)[2]));
	pthread_mutex_unlock(&((philo->data->sdrei)[2]));
	while (1)
	{
		pthread_mutex_lock(&((philo->data->sdrei)[4]));
		if (rout_check(philo))
		{
			pthread_mutex_unlock(&((philo->data->sdrei)[4]));
			if (think(philo))
				return (NULL);
		}
		else
			pthread_mutex_unlock(&((philo->data->sdrei)[4]));
		if (philo->thought || !philo->n_eaten)
			if (eat(philo))
				return (NULL);
		if (my_sleep(philo))
			return (NULL);
	}
	return (NULL);
}
