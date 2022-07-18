/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:27:15 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 18:37:10 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	putstr_error(char *error)
{
	if (error)
		while (*error)
			write(2, (void *)error++, 1);
	return (1);
}

int	digitize(UINT (*t)[5], char **av)
{
	int	i;
	int	len;

	i = 0;
	len = len_tab(av + 1);
	while (i < 4)
	{
		if (phil_atoi(av[i + 1], &((*t)[i])))
			return (1);
		i++;
	}
	if (len == 5)
		if (phil_atoi(av[i + 1], &((*t)[i])))
			return (1);
	return (0);
}

int	phil_atoi(char *str, UINT *val_to_fill)
{
	long unsigned int	res;
	int					i;
	int					len;
	int					start;

	res = 0;
	i = 0;
	len = 0;
	start = 1;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] == '-' || !(str[i] > 47 && str[i] < 58))
			return (1);
		if (str[i] != '0')
			start = 0;
		res = res * 10 + (str[i] - 48);
		i++;
		if (!start)
			len++;
	}
	if (len > 10 || res > UIMAX)
		return (1);
	return ((*val_to_fill) = (UINT)res, 0);
}
