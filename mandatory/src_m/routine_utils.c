/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 03:50:42 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/17 06:10:13 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

int	eat_sup_die(t_philo *philo)
{
	if (philo->data->t_eat >= philo->data->t_die)
	{
		get_message(philo, "\x1B[32mis eating\e[0m");
		usleep((philo->data->t_die - get_timestamp(philo->data->t_launch)) * 1000 - 10);
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		get_message(philo, "is dead");
		return (1);
	}
		pthread_mutex_unlock(&philo->data->mut[philo->next->id - 1]);
		pthread_mutex_unlock(&philo->data->mut[philo->id - 1]);
		return (0);
}
