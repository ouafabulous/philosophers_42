/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 16:48:14 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 04:20:37 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_m/philo.h"


void	free_philo(t_philo **philo, int n_phil)
{
	t_philo	*tmp;
	int		i;

	i = -1;
	if (philo)
	{
		while (++i < n_phil && *philo)
		{
			tmp = *philo;
			*philo = (*philo)->next;
			if (tmp)
			{
				free(tmp);
				tmp = NULL;
			}
		}
		philo = NULL;
	}
}

t_philo	*create_philo(int id, t_data *data)
{
	t_philo *ret;

	ret = (t_philo *)malloc(sizeof(t_philo));
	if (!ret)
		return (NULL);
	ret->id = id;
	ret->data = data;
	ret->n_eaten = 0;
	ret->thought = 0;
	ret->next = NULL;
	return (ret);
}

int add_sib_last(t_philo **philo, int id, t_data *data)
{
	t_philo *tmp;

	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_philo(id, data);
	if (!tmp->next)
	{
		free_philo(philo, data->n_phil);
		return (1);
	}
	return (0);
}

void make_it_circle(t_philo **philo)
{
	t_philo *tmp;

	if (!philo || !*philo)
		return ;
	tmp = *philo;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = *philo;
}

int fill_philo_list(t_philo **philo, t_data *data, UINT num_p)
{
	UINT i;

	i = 0;
	while (i < num_p)
	{
		if (!*philo)
		{
			*philo = create_philo(i + 1, data);
			if (!*philo)
				return (putstr_error("Error in creating the philo struct\n"));
		}
		else if (add_sib_last(philo, i + 1, data))
			return (putstr_error("Error in creating the philo struct\n"));
		i++;
	}
	make_it_circle(philo);
	return (0);
}
