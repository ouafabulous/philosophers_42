/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:24:56 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/17 20:01:21 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

UINT	get_timestamp(struct timeval t_launch)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - t_launch.tv_sec) * 1000 + (UINT)((now.tv_usec - t_launch.tv_usec) * 0.001));
}

int	get_message(t_philo *philo, char *str, int i)
{
	if (!stop_simulation(philo, philo->data->n_eat, str, i))
	{
		pthread_mutex_lock(&(philo->data->sdrei[0]));
		printf("%u %d %s\n", get_timestamp(philo->data->t_launch), philo->id, str);
		pthread_mutex_unlock(&(philo->data->sdrei[0]));
		return (0);
	}
	return (1);
}
