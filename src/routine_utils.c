/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 03:50:42 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 18:31:57 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	eat_sup_die(t_philo *philo)
{
	if (philo->data->t_eat >= philo->data->t_die)
	{
		get_message(philo, "\x1B[32mis eating\e[0m", 0);
		usleep((philo->data->t_die
				- get_timestamp(philo->data->t_launch)) * 1000 - 10);
		if (philo->id % 2)
		{
			pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		}
		else
		{
			pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
			pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		}
		get_message(philo, "is dead", 0);
		return (1);
	}
	return (0);
}

int	think_1(t_philo *philo)
{
	philo->data->i--;
	pthread_mutex_unlock(&((philo->data->sdrei)[4]));
	if (get_message(philo, "is thinking", 0))
		return (1);
	if (philo->data->t_eat > 30)
		usleep(philo->data->t_eat * 1000 - 30000);
	else
		usleep(philo->data->t_eat * 1000);
	return (0);
}

int	think_2(t_philo *philo)
{
	pthread_mutex_unlock(&((philo->data->sdrei)[4]));
	if (get_message(philo, "is thinking", 0))
	{
		return (1);
	}
	if (philo->data->t_die - get_timestamp(philo->lm_time)
		> (philo->data->t_eat - philo->data->t_sleep + 1) * 1000)
		usleep((philo->data->t_eat - philo->data->t_sleep + 1) * 1000);
	return (0);
}

int	rout_check(t_philo *philo)
{
	if ((philo->data->i && (philo->id % 2))
		|| (!philo->data->i && !(philo->id % 2) && philo->n_eaten)
		|| (!philo->data->i && (philo->id % 2)))
		return (1);
	return (0);
}
