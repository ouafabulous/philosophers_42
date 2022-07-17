/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threader.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:54:49 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/17 03:35:03 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

int	create_threads(t_data *data, pthread_t **th)
{
	*th = (pthread_t *)malloc(data->n_phil * sizeof(pthread_t));
	if (!*th)
		return (1);
	return (0);
}

int	malmutex_error(t_data *data, pthread_t **th, int err, int i)
{
	int	j;

	j = -1;
	free(*th);
	if (err == 3)
	{
		while (++j < i)
				pthread_mutex_destroy(&(data->mut)[j]);
		free(data->sdrei);
	}
	if (err == 2 || err == 3)
		free(data->mut);
	return (putstr_error("Error!\n"));
}

int	init_mutexes(t_data *data, pthread_t **th)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	data->mut = malloc((data->n_phil) * sizeof(pthread_mutex_t));
	if (!data->mut)
		return (malmutex_error(data, th, 1, -1));
	data->sdrei = malloc(5 * sizeof(pthread_mutex_t));
	if (!data->sdrei)
		return (malmutex_error(data, th, 2, -1));
	while (++i < data->n_phil)
		if (pthread_mutex_init(&(data->mut)[i], NULL))
			return (malmutex_error(data, th, 3, i));
	i = -1;
	while (++i < 5)
	{
		if (pthread_mutex_init(&(data->sdrei)[i], NULL))
		{
			while (++j < i)
				pthread_mutex_destroy(&(data->sdrei)[j]);
			return (malmutex_error(data, th, 3, data->n_phil));
		}
	}
	return (0);
}

int	sub_threader(pthread_t *th, t_philo **philo)
{
	int		i;

	i = -1;
	pthread_mutex_lock(&((*philo)->data->sdrei)[2]);
	while (++i < (*philo)->data->n_phil)
	{
		if (pthread_create(&(th[i]), NULL, &routine, *philo))
			return (pthread_mutex_unlock(&((*philo)->data->sdrei)[2]), putstr_error("Error!\n"));
		(*philo) = (*philo)->next;
	}
	gettimeofday(&((*philo)->data->t_launch), NULL);
	pthread_mutex_unlock(&((*philo)->data->sdrei)[2]);
	return (0);
}

int	threader(t_data *data, t_philo **philo)
{
	pthread_t	*th;
	int			i;

	i = -1;
	if (fill_philo_list(philo, data, data->n_phil))
		return (1);
	if (create_threads(data, &th))
		return (free_philo(philo, data->n_phil), 1);
	if (init_mutexes(data, &th))
		return (free_philo(philo, data->n_phil), 1);
	if (sub_threader(th, philo))
		return (free_all(&th, data, philo), 1);
	while (++i < data->n_phil)
	{
		if (pthread_join(th[i], NULL))
			return (free_all(&th, data, philo), 1);
	}
	return (free_all(&th, data, philo), 0);
}
