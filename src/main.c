/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:38:43 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 17:05:46 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(UINT t[5], t_data *data, char **argv)
{
	data->n_phil = (int)(t[0]);
	if (!data->n_phil)
		return (1);
	data->t_die = t[1];
	if (!data->t_die)
		return (1);
	data->t_eat = t[2];
	data->t_sleep = t[3];
	data->t_think = t[1] - (t[2] + t[3]);
	if (len_tab(argv + 1) == 5)
		data->n_eat = (int)t[4];
	else
		data->n_eat = -1;
	if (!data->n_eat)
		return (2);
	data->all_eaten = 0;
	data->state = 0;
	if ((data->n_phil % 2))
		data->i = data->n_phil / 2 + 1;
	else
		data->i = data->n_phil / 2;
	return (0);
}

int	main(int argc, char **argv)
{
	UINT	t[5];
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (argc >= 5 && argc <= 6)
	{
		if (digitize(&t, argv))
			return (putstr_error(ERR_ARGS_1));
		if (init_data(t, &data, argv))
			return (putstr_error(ERR_ARGS_2));
		threader(&data, &philo);
	}
	else
		return (putstr_error(ERR_ARGS_3));
	return (0);
}
