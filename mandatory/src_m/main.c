/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:38:43 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/17 06:12:32 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"

void	init_data(UINT t[5], t_data *data)
{
	data->n_phil = (int)(t[0]);
	data->t_die = t[1];
	data->t_eat = t[2];
	data->t_sleep = t[3];
	data->t_think = t[1] - (t[2] + t[3]);
	data->n_eat = (int)t[4];
	data->all_eaten = 0;
	data->state = 0;
	if ((data->n_phil % 2))
		data->i = data->n_phil / 2 + 1;
	else
		data->i = data->n_phil / 2;
}

int main(int argc, char **argv)
{
	UINT	t[5];
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (digitize(&t, argv))
			return (putstr_error("Make sure the values introduced are unsigned, non-negative integers!\n"));
		init_data(t, &data);
		threader(&data, &philo);
	}
	else
		return (putstr_error("Make sure you are giving the right number of arguments (4 or 5)!\n"));
	return 0;
}
