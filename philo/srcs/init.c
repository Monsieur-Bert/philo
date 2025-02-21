/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:39:24 by antauber          #+#    #+#             */
/*   Updated: 2025/02/21 17:03:18 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <philo.h>

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
	while(i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal = table->start_time;
		table->philos[i].l_fork = &table->mtx_forks[i];
		table->philos[i].r_fork = &table->mtx_forks[(i + 1) % table->nb_philos];
		table->philos[i].table = table;
		i++;
	}
}

void	start_simulation(t_table *table)
{
	t_philo	*philos;
	int	i;

	philos = table->philos;
	i = 0;
	while(i < table->nb_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}
	while (1)
	{
		i = 0;
		while (i < table->nb_philos)
		{
			LOCK(&table->mtx_meals[i]);
			if (get_time() - table->philos[i].last_meal >= table->time_to_die)
			{
				UNLOCK(&table->mtx_meals[i]);
				LOCK(&table->mtx_simu);
				table->simu = false;
				UNLOCK(&table->mtx_simu);
				status_display(get_time() - table->start_time, &table->philos[i], DIE, true);
				return ;
			}
			UNLOCK(&table->mtx_meals[i]);
			LOCK(&table->mtx_meals[i]);
			if (table->philos[i].nb_meals == table->meal_goal)
			{
				UNLOCK(&table->mtx_meals[i]);
				LOCK(&table->mtx_simu);
				table->simu = false;
				UNLOCK(&table->mtx_simu);
				return ;
			}
			UNLOCK(&table->mtx_meals[i]);
			i++;
		}
	}
}
