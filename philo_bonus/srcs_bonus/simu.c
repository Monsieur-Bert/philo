/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:40:00 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 18:06:06 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	cemetery_gate(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (table->ph_pids[i] >= 0)
			kill(table->ph_pids[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		waitpid(table->ph_pids[i], NULL, 0);
		i++;
	}
}

void	*monitor_death(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	sem_wait(table->sem_death);
	sem_wait(table->sem_simu);
	table->simu = false;
	sem_post(table->sem_simu);
	return (NULL);
}

void	*monitor_full(void *data)
{
	t_table	*table;
	int		full;

	table = (t_table *)data;
	full = 0;
	while (full < table->nb_philos)
	{
		sem_wait(table->sem_full);
		full ++;
	}
	sem_wait(table->sem_simu);
	table->simu = false;
	sem_post(table->sem_simu);
	return (NULL);
}

void	start_simulation(t_table *table)
{
	int		i;

	i = 0;
	pthread_create(&table->th_death, NULL, &monitor_death, table);
	pthread_detach(table->th_death);
	if (table->meal_goal > 0)
	{
		pthread_create(&table->th_full, NULL, &monitor_full, table);
		pthread_detach(table->th_full);
	}
	while (i < table->nb_philos)
	{
		table->ph_pids[i] = fork();
		if (table->ph_pids[i] == 0)
		philo_process(&table->philos[i]);
		i++;
	}
	while (is_simu_ok(table))
	usleep(1000);
	cemetery_gate(table);
}
