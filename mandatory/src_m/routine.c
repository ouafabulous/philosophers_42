/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 18:10:55 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 04:18:34 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

void *handle_one(t_philo *philo)
{
	if (!philo->data->t_die || get_timestamp(philo->data->t_launch) >= philo->data->t_die)
		get_message(philo, "died", 0);
	else
	{
		get_message(philo, "has taken a fork", 0);
		usleep((philo->data->t_die - get_timestamp(philo->data->t_launch)) * 1000);
		get_message(philo, "died", 0);
	}
	return (NULL);
}

int think(t_philo *philo)
{
	philo->thought = 1;
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&((philo->data->sdrei)[4]));
	if (philo->data->i && (philo->id % 2))
	{
		philo->data->i--;
		pthread_mutex_unlock(&((philo->data->sdrei)[4]));
		if (get_message(philo, "is thinking", 0))
		{
			return (1);
		}
		if (philo->data->t_eat > 30)
			usleep(philo->data->t_eat * 1000 - 30000);
		else
			usleep(philo->data->t_eat * 1000);
	}
	else
	{
		pthread_mutex_unlock(&((philo->data->sdrei)[4]));
		if (get_message(philo, "is thinking", 0))
		{
			return (1);
		}
		usleep((philo->data->t_eat - philo->data->t_sleep + 1) * 1000);
	}
	if ((philo->id % 2))
	{
		while (philo->data->mut[philo->id - 1].__data.__lock && philo->data->mut[philo->next->id - 1].__data.__lock)
		{
			// printf(" I'm philo: %d and here are the forks I need to eat with: %d, %d\n",philo->id, philo->data->mut[philo->next->id - 1].__data.__lock, philo->data->mut[philo->id - 1].__data.__lock);
			if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
				return (1);
			usleep(10);
		}
	}
	else
	{
		// while (philo->data->mut[philo->next->id - 1].__data.__lock && philo->data->mut[philo->id - 1].__data.__lock)
		while (philo->data->mut[philo->next->id - 1].__data.__lock)
		{
			// printf(" I'm philo: %d and here are the forks I need to eat with: %d, %d\n",philo->id, philo->data->mut[philo->next->id - 1].__data.__lock, philo->data->mut[philo->id - 1].__data.__lock);
			if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
				return (1);
			usleep(10);
		}
	}
	return (0);
}

int eat_even(t_philo *philo)
{
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&philo->data->mut[philo->id - 1]);
	if (get_message(philo, "has taken a fork", 0))
		return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
	pthread_mutex_lock(&philo->data->mut[philo->next->id - 1]);
	if (get_message(philo, "has taken a fork", 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
	}
	if (eat_sup_die(philo))
		return (1);
	philo->n_eaten++;
	if (philo->n_eaten == philo->data->n_eat)
	{
		pthread_mutex_lock(&(philo->data->sdrei[3]));
		philo->data->all_eaten++;
		if (philo->data->all_eaten == philo->data->n_phil)
		{
			pthread_mutex_unlock(&(philo->data->sdrei[3]));
			gettimeofday(&philo->lm_time, NULL);
			if (get_message(philo, "is eating", 1))
			{
				pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
				pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
				return (1);
			}
			else
			{
				usleep(philo->data->t_eat * 1000);
				pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
				pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
				return (1);
			}
		}
		pthread_mutex_unlock(&(philo->data->sdrei[3]));
	}
	gettimeofday(&philo->lm_time, NULL);
	if (get_message(philo, "is eating", 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		return (1);
	}
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
	pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
	return (0);
}

int eat_odd(t_philo *philo)
{
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&philo->data->mut[philo->next->id - 1]);
	if (get_message(philo, "has taken a fork", 0))
		return (pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]), 1);
	pthread_mutex_lock(&philo->data->mut[philo->id - 1]);
	if (get_message(philo, "has taken a fork", 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		return (pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]), 1);
	}
	if (eat_sup_die(philo))
		return (1);
	philo->n_eaten++;
	if (philo->n_eaten == philo->data->n_eat)
	{
		pthread_mutex_lock(&(philo->data->sdrei[3]));
		philo->data->all_eaten++;
		if (philo->data->all_eaten == philo->data->n_phil)
		{
			pthread_mutex_unlock(&(philo->data->sdrei[3]));
			gettimeofday(&philo->lm_time, NULL);
			if (get_message(philo, "is eating", 1))
			{
				pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
				pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
				return (1);
			}
			else
			{
				usleep(philo->data->t_eat * 1000);
				pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
				pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
				return (1);
			}
		}
		pthread_mutex_unlock(&(philo->data->sdrei[3]));
	}
	gettimeofday(&philo->lm_time, NULL);
	if (get_message(philo, "is eating", 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		return (1);
	}
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
	pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
	return (0);
}

int eat(t_philo *philo)
{
	philo->thought = 0;
	if (philo->id % 2)
	{
		if (eat_odd(philo))
			return (1);
	}
	else
	{
		if (eat_even(philo))
			return (1);
	}
	return (0);
}

int my_sleep(t_philo *philo)
{
	UINT diff;

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

void *routine(void *args)
{
	t_philo *philo;

	philo = (t_philo *)args;
	if (philo->data->n_phil == 1)
		return (handle_one(philo), NULL);
	pthread_mutex_lock(&((philo->data->sdrei)[2]));
	pthread_mutex_unlock(&((philo->data->sdrei)[2]));
	while (1)
	{
		pthread_mutex_lock(&((philo->data->sdrei)[4]));
		if ((philo->data->i && (philo->id % 2)) || (!philo->data->i && !(philo->id % 2) && philo->n_eaten) || (!philo->data->i && (philo->id % 2)))
		{
			pthread_mutex_unlock(&((philo->data->sdrei)[4]));
			if (think(philo))
				return (NULL);
		}
		else
			pthread_mutex_unlock(&((philo->data->sdrei)[4]));
		if (philo->thought || !philo->n_eaten)
		{
			if (eat(philo))
				return (NULL);
		}
		if (my_sleep(philo))
			return (NULL);
	}
	return (NULL);
}
