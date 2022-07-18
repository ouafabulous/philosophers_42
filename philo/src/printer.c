/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 19:24:56 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 19:57:59 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

UINT	get_timestamp(struct timeval t_launch)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - t_launch.tv_sec) * 1000
		+ (UINT)((now.tv_usec - t_launch.tv_usec) * 0.001));
}

void	print_in_colors(t_philo *philo, char *str)
{
	if (!ft_strncmp(str, DIE, 7))
		printf("%s%u %d %s%s\n", RED, get_timestamp(philo->data->t_launch),
			philo->id, str, RESET);
	else if (!ft_strncmp(str, THINK, 11))
		printf("%s%u %d %s%s\n", MAGENTA, get_timestamp(philo->data->t_launch),
			philo->id, str, RESET);
	else if (!ft_strncmp(str, SLEEP, 11))
		printf("%s%u %d %s%s\n", CYAN, get_timestamp(philo->data->t_launch),
			philo->id, str, RESET);
	else if (!ft_strncmp(str, TAKE_FORK, 16))
		printf("%s%u %d %s%s\n", YELLOW, get_timestamp(philo->data->t_launch),
			philo->id, str, RESET);
	else
		printf("%s%u %d %s%s\n", GREEN, get_timestamp(philo->data->t_launch),
			philo->id, str, RESET);
}

int	get_message(t_philo *philo, char *str, int i)
{
	if (!stop_simulation(philo, philo->data->n_eat, str, i))
	{
		pthread_mutex_lock(&(philo->data->sdrei[0]));
		print_in_colors(philo, str);
		pthread_mutex_unlock(&(philo->data->sdrei[0]));
		return (0);
	}
	return (1);
}
