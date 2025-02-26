/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:39:24 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 11:23:15 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->mtx_display, NULL);
	pthread_mutex_init(&table->mtx_simu, NULL);
	table->mtx_forks = malloc(sizeof(t_mutex) * table->nb_philos);
	if (table->mtx_forks == NULL)
		return (1);
	table->mtx_meals = malloc(sizeof(t_mutex) * table->nb_philos);
	if (table->mtx_meals == NULL)
	{
		free(table->mtx_forks);
		return (1);
	}
	while (i < table->nb_philos)
	{
		pthread_mutex_init(&table->mtx_forks[i], NULL);
		pthread_mutex_init(&table->mtx_meals[i], NULL);
		i++;
	}
	return (0);
}

static void	give_forks(t_table *table, int *i)
{
	if ((*i + 1) % 2 == 0)
	{
		table->philos[*i].l_fork = &table->mtx_forks[*i];
		table->philos[*i].r_fork = &table->mtx_forks[(*i + 1)
			% table->nb_philos];
	}
	else
	{
		table->philos[*i].r_fork = &table->mtx_forks[*i];
		table->philos[*i].l_fork = &table->mtx_forks[(*i + 1)
			% table->nb_philos];
	}
	table->philos[*i].table = table;
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->philos == NULL)
	{
		free(table->mtx_forks);
		free(table->mtx_meals);
		return (1);
	}
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal = table->start;
		give_forks(table, &i);
		i++;
	}
	return (0);
}
