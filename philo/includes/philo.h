/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 15:40:57 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/18 20:37:22 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define UINT unsigned int
# define UIMAX 4294967295
# define ERR_ARGS_1 "Only non-negative integers accepted!\n"
# define ERR_ARGS_2 "One of these is null: num_philos, t_to_die, num_to_eat!\n"
# define ERR_ARGS_3 "Please give the right number of arguments (4 or 5)!\n"
# define TAKE_FORK "has taken a fork 🔱"
# define EAT "is eating 🍕"
# define SLEEP "is sleeping 💤"
# define THINK "is thinking 💭"
# define DIE "is dead 💀"

# define RESET   "\033[0m"
# define RED     "\033[1m\033[31m"
# define GREEN   "\033[1m\033[32m"
# define YELLOW  "\033[1m\033[33m"
# define MAGENTA "\033[1m\033[35m"
# define CYAN    "\033[1m\033[36m"

typedef struct s_data
{
	int				i;
	int				n_phil;
	UINT			t_die;
	UINT			t_eat;
	UINT			t_sleep;
	UINT			t_think;
	int				n_eat;
	int				state;
	pthread_mutex_t	*mut;
	pthread_mutex_t	*sdrei;
	int				all_eaten;
	struct timeval	t_launch;
}				t_data;

typedef struct s_philo
{
	unsigned int	id;
	struct timeval	lm_time;
	int				n_eaten;
	int				thought;
	t_data			*data;
	struct s_philo	*next;
}				t_philo;

//---------------------parser.c-------------------------------------
int		len_tab(char **tab);
int		putstr_error(char *error);
int		digitize(UINT (*t)[5], char **av);
int		phil_atoi(char *str, unsigned int *val_to_fill);

//---------------------threader.c-----------------------------------
int		create_threads(t_data *data, pthread_t **th);
int		malmutex_error(t_data *data, pthread_t **th, int err, int i);
int		init_mutexes(t_data *data, pthread_t **th);
int		threader(t_data *data, t_philo **philo);

//---------------------philo_creator.c-----------------------------
void	free_philo(t_philo **philo, int n_phil);
t_philo	*create_philo(int id, t_data *data);
int		add_sib_last(t_philo **philo, int id, t_data *data);
void	make_it_circle(t_philo **philo);
int		fill_philo_list(t_philo **philo, t_data *data, UINT num_p);

//---------------------utils.c-------------------------------------
void	free_all(pthread_t **th, t_data *data, t_philo **philo);

//---------------------printer.c-----------------------------------
UINT	get_timestamp(struct timeval t_launch);
void	print_in_colors(t_philo *philo, char *str);
int		get_message(t_philo *philo, char *str, int i);

//---------------------routine.c-----------------------------------
void	*handle_one(t_philo *philo);
int		think(t_philo *philo);
int		eat(t_philo *philo);
int		my_sleep(t_philo *philo);
void	*routine(void *args);

//---------------------routine_utils.c-----------------------------
int		eat_sup_die(t_philo *philo);
int		think_1(t_philo *philo);
int		think_2(t_philo *philo);
int		rout_check(t_philo *philo);

//---------------------eat_tutils.c--------------------------------
int		eat_even_1(t_philo *philo);
int		eat_even(t_philo *philo);
void	eat_odd1(t_philo *philo);
int		eat_odd2(t_philo *philo);
int		eat_odd(t_philo *philo);

//---------------------simulation_stopper.c------------------------
int		ft_strncmp(char *s1, char *s2, size_t n);
int		is_any_p_dead(t_philo *philo);
int		there_is_blood(t_philo *philo, char *str);
int		all_eaten(t_philo *philo, int n_eat, int i);
int		stop_simulation(t_philo *philo, int n_eat, char *str, int i);

#endif
