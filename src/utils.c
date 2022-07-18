/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:32:05 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 16:39:43 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(pthread_t **th, t_data *data, t_philo **philo)
{
	int	i;

	i = -1;
	free(*th);
	while (++i < (*philo)->data->n_phil)
		pthread_mutex_destroy(&(data->mut[i]));
	free(data->mut);
	i = -1;
	while (++i < 5)
		pthread_mutex_destroy(&(data->sdrei[i]));
	free(data->sdrei);
	free_philo(philo, data->n_phil);
}
