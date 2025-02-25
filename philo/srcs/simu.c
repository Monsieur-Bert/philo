/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:40:00 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 09:40:13 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	monitoring_loop(t_table *table, int *i)
{
	bool	is_full;

	LOCK(&table->mtx_meals[*i]);
	if (get_time() - table->philos[*i].last_meal >= table->t_to_die)
	{
		LOCK(&table->mtx_simu);
		table->simu = false;
		UNLOCK(&table->mtx_simu);
		display(get_time() - table->start, &table->philos[*i], DIE, true);
		UNLOCK(&table->mtx_meals[*i]);
		return (false);
	}
	UNLOCK(&table->mtx_meals[*i]);
	is_full = table_is_full(table);
	LOCK(&table->mtx_meals[*i]);
	if (is_full && table->meal_goal != -1)
	{
		LOCK(&table->mtx_simu);
		table->simu = false;
		UNLOCK(&table->mtx_simu);
		UNLOCK(&table->mtx_meals[*i]);
		return (false);
	}
	UNLOCK(&table->mtx_meals[*i]);
	return (true);
}

void	start_simulation(t_table *table)
{
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
		while (++i < table->nb_philos)
		{
			if (!monitoring_loop(table, &i))
			{
				usleep(250);
				return ;
			}
		}
		usleep(1000);
	}
}
