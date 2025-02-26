/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:39:24 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 17:55:06 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	init_semaphores(t_table *table)
{
	//proteger tout ca ou enlever le return
	sem_unlink("/simu");
	sem_unlink("/death");
	sem_unlink("/full");
	sem_unlink("/meal_access");
	sem_unlink("/display");
	sem_unlink("/forks");
	table->sem_simu = sem_open("/simu", O_CREAT, 0644, 1);
	table->sem_death = sem_open("/death", O_CREAT, 0644, 0);
	table->sem_full = sem_open("/full", O_CREAT, 0644, 0);
	table->sem_meal_access = sem_open("/meal_access", O_CREAT, 0644, 1);
	table->sem_display = sem_open("/display", O_CREAT, 0644, 1);
	table->sem_forks = sem_open("/forks", O_CREAT, 0644, table->nb_philos);
	return (0);
}

int	init_philos(t_table *table)
{
	int		i;

	i = 0;
	table->philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (table->philos == NULL)
		return (1);
	table->ph_pids = malloc(sizeof(t_pid) * table->nb_philos);
	if (table->ph_pids == NULL)
	{
		free(table->philos);
		return (1);
	}
	while (i < table->nb_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].nb_meals = 0;
		table->philos[i].last_meal = table->start;
		table->philos[i].table = table;
		i++;
	}
	return (0);
}
