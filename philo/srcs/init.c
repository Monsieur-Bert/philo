/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:39:24 by antauber          #+#    #+#             */
/*   Updated: 2025/02/24 17:08:58 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->mtx_display, NULL);
	pthread_mutex_init(&table->mtx_simu, NULL);
	table->mtx_forks = malloc(sizeof(t_mutex) * table->nb_philos);
	if (table->mtx_forks == NULL)
		exit(EXIT_FAILURE);
	table->mtx_meals = malloc(sizeof(t_mutex) * table->nb_philos);
	if (table->mtx_meals == NULL)
	{
		free(table->mtx_forks);
		exit(EXIT_FAILURE);
	}
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&table->mtx_forks[i], NULL);
		pthread_mutex_init(&table->mtx_meals[i], NULL);
		i++;
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->philos == NULL)
	{
		free(table->mtx_forks);
		free(table->mtx_meals);
		exit (EXIT_FAILURE);
	}
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal = table->start;
		if ((i + 1) % 2 == 0)
		{
			table->philos[i].l_fork = &table->mtx_forks[i];
			table->philos[i].r_fork = &table->mtx_forks[(i + 1) % table->nb_philos];
		}
		else
		{
			table->philos[i].r_fork = &table->mtx_forks[i];
			table->philos[i].l_fork = &table->mtx_forks[(i + 1) % table->nb_philos];
		}
		table->philos[i].table = table;
		i++;
	}
}

void	monitoring_loop(t_table *table, bool *should_stop, int *i)
{
	int	total_meals;

	LOCK(&table->mtx_meals[*i]);
	if (get_time() - table->philos[*i].last_meal >= table->time_to_die)
	{
		LOCK(&table->mtx_simu);
		table->simu = false;
		UNLOCK(&table->mtx_simu);
		display(get_time() - table->start, &table->philos[*i], DIE, true);
		*should_stop = true;
		UNLOCK(&table->mtx_meals[*i]);
		return ;
	}
	UNLOCK(&table->mtx_meals[*i]);
	total_meals = get_total_meals(table);
	LOCK(&table->mtx_meals[*i]);
	if (total_meals == table->meal_goal * table->nb_philos)
	{
		LOCK(&table->mtx_simu);
		table->simu = false;
		UNLOCK(&table->mtx_simu);
		*should_stop = true;
		UNLOCK(&table->mtx_meals[*i]);
		return ;
	}
	UNLOCK(&table->mtx_meals[*i]);
}

void	start_simulation(t_table *table)
{
	bool	should_stop;
	int		i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&table->philos[i].thread, NULL, philo_routine,
			&table->philos[i]);
		i++;
	}
	while (1)
	{
		i = -1;
		should_stop = false;
		while (++i < table->nb_philos)
		{
			monitoring_loop(table, &should_stop, &i);
			if (should_stop)
			{
				usleep(250);
				return ;
			}
		}
		usleep(1000);
	}
}
