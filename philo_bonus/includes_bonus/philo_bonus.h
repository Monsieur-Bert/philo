/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:43:06 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 17:13:38 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <display.h>
# include <signal.h>

//# include <string.h>

typedef pthread_t	t_pthread;
typedef sem_t		t_sem;
typedef pid_t		t_pid;

typedef struct s_table	t_table;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	time_t		last_meal;
	t_table		*table;
	t_pthread	th_philo;
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
	t_pid		*ph_pids;
	t_sem		*sem_simu;
	t_sem		*sem_death;
	t_sem		*sem_full;
	t_sem		*sem_meal_access;
	t_sem		*sem_display;
	t_sem		*sem_forks;
	t_pthread	th_death;
	t_pthread	th_full;
}	t_table;

int		parse(int argc, char **argv, t_table *data);
int		init_semaphores(t_table *table);
int		init_philos(t_table *table);

void	delayed_start(time_t time);
void	ft_usleep(time_t target, t_table *table);
time_t	get_time(void);

void	display(time_t time, t_philo *philo, char *log, bool is_dead);
bool	is_simu_ok(t_table *table);
void	clean_off_the_table(t_table *table, bool is_child);

void	philo_process(t_philo *philo);
void	start_simulation(t_table *table);

#endif