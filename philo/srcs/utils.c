/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:13:44 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 09:36:15 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	table_is_full(t_table *table)
{
	int		i;
	bool	is_full;

	is_full = false;
	i = 0;
	while (i < table->nb_philos)
	{
		LOCK(&table->mtx_meals[i]);
		if (table->philos[i].nb_meals < table->meal_goal)
		{
			UNLOCK(&table->mtx_meals[i]);
			return (is_full);
		}
		UNLOCK(&table->mtx_meals[i]);
		i++;
	}
	is_full = true;
	return (is_full);
}

bool	is_simu_ok(t_table *table)
{
	bool	status;

	LOCK(&table->mtx_simu);
	status = table->simu;
	UNLOCK(&table->mtx_simu);
	return (status);
}

void	display(time_t time, t_philo *philo, char *log, bool death)
{
	if (is_simu_ok(philo->table))
	{
		LOCK(&philo->table->mtx_display);
		printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id,
			RESET, log);
		UNLOCK(&philo->table->mtx_display);
	}
	else if (death)
	{
		usleep(1);
		LOCK(&philo->table->mtx_display);
		printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id,
			RESET, log);
		UNLOCK(&philo->table->mtx_display);
	}
}

void	clean_off_the_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_destroy(&table->mtx_forks[i]);
		pthread_mutex_destroy(&table->mtx_meals[i]);
		i++;
	}
	pthread_mutex_destroy(&table->mtx_display);
	pthread_mutex_destroy(&table->mtx_simu);
	free(table->mtx_forks);
	free(table->mtx_meals);
	free(table->philos);
}
