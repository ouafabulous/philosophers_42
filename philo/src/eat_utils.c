/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:17:54 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 19:24:12 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_even_1(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->sdrei[3]));
	if (philo->data->all_eaten < philo->data->n_phil - 1)
		philo->data->all_eaten++;
	if (philo->data->all_eaten + 1 == philo->data->n_phil)
	{
		pthread_mutex_unlock(&(philo->data->sdrei[3]));
		gettimeofday(&philo->lm_time, NULL);
		if (get_message(philo, EAT, 0))
		{
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
			return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
		}
		else
		{
			usleep(philo->data->t_eat * 1000);
			pthread_mutex_lock(&(philo->data->sdrei[3]));
			philo->data->all_eaten++;
			pthread_mutex_unlock(&(philo->data->sdrei[3]));
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
			return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
		}
	}
	pthread_mutex_unlock(&(philo->data->sdrei[3]));
	return (0);
}

int	eat_even(t_philo *philo)
{
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&philo->data->mut[philo->id - 1]);
	if (get_message(philo, TAKE_FORK, 0))
		return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
	pthread_mutex_lock(&philo->data->mut[philo->next->id - 1]);
	if (get_message(philo, TAKE_FORK, 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
	}
	if (eat_sup_die(philo))
		return (1);
	philo->n_eaten++;
	if (philo->n_eaten == philo->data->n_eat && eat_even_1(philo))
		return (1);
	gettimeofday(&philo->lm_time, NULL);
	if (get_message(philo, EAT, 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 1);
	}
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
	return (pthread_mutex_unlock(&philo->data->mut[philo->id - 1]), 0);
}

void	eat_odd1(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
}

int	eat_odd2(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->sdrei[3]));
	if (philo->data->all_eaten < philo->data->n_phil - 1)
		philo->data->all_eaten++;
	else if (philo->data->all_eaten + 1 == philo->data->n_phil)
	{
		pthread_mutex_unlock(&(philo->data->sdrei[3]));
		gettimeofday(&philo->lm_time, NULL);
		if (get_message(philo, EAT, 0))
		{
			pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
			return (1);
		}
		else
		{
			usleep(philo->data->t_eat * 1000);
			pthread_mutex_lock(&(philo->data->sdrei[3]));
			philo->data->all_eaten++;
			pthread_mutex_unlock(&(philo->data->sdrei[3]));
			pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
			return (1);
		}
	}
	return (pthread_mutex_unlock(&(philo->data->sdrei[3])), 0);
}

int	eat_odd(t_philo *philo)
{
	if (stop_simulation(philo, philo->data->n_eat, NULL, 0))
		return (1);
	pthread_mutex_lock(&philo->data->mut[philo->next->id - 1]);
	if (get_message(philo, TAKE_FORK, 0))
		return (eat_odd1(philo), 1);
	pthread_mutex_lock(&philo->data->mut[philo->id - 1]);
	if (get_message(philo, TAKE_FORK, 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		return (eat_odd1(philo), 1);
	}
	if (eat_sup_die(philo))
		return (1);
	philo->n_eaten++;
	if (philo->n_eaten == philo->data->n_eat && eat_odd2(philo))
		return (1);
	gettimeofday(&philo->lm_time, NULL);
	if (get_message(philo, EAT, 0))
	{
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		return (eat_odd1(philo), 1);
	}
	usleep(philo->data->t_eat * 1000);
	pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
	return (eat_odd1(philo), 0);
}
