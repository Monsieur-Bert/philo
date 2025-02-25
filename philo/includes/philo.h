/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:43:06 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 09:40:34 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <display.h>

# define LOCK	pthread_mutex_lock
# define UNLOCK	pthread_mutex_unlock

typedef pthread_t		t_pthread;
typedef pthread_mutex_t	t_mutex;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	t_pthread	thread;
	int			nb_meals;
	time_t		last_meal;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_table		*table;
}	t_philo;

typedef struct s_table
{
	bool		simu;
	int			nb_philos;
	time_t		t_to_die;
	time_t		t_to_eat;
	time_t		t_to_sleep;
	time_t		start;
	int			meal_goal;
	t_philo		*philos;
	t_pthread	monitor;
	t_mutex		mtx_display;
	t_mutex		mtx_simu;
	t_mutex		*mtx_forks;
	t_mutex		*mtx_meals;
}	t_table;

int		parse(int argc, char **argv, t_table *data);
void	init_mutex(t_table *table);
void	init_philos(t_table *table);

void	delayed_start(time_t time);
void	ft_usleep(time_t target, t_table *table);
time_t	get_time(void);

bool	table_is_full(t_table *table);
bool	is_simu_ok(t_table *philo);
void	display(time_t time, t_philo *philo, char *log, bool death);
void	clean_off_the_table(t_table *table);

void	*philo_routine(void *data);
void	start_simulation(t_table *table);

#endif