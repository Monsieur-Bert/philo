/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:13:44 by antauber          #+#    #+#             */
/*   Updated: 2025/02/24 16:15:53 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	get_total_meals(t_table *table)
{
	int	total_meals;
	int	i;

	total_meals = 0;
	i = 0;
	while (i < table->nb_philos)
	{
		LOCK(&table->mtx_meals[i]);
		total_meals += table->philos[i].nb_meals;
		UNLOCK(&table->mtx_meals[i]);
		i++;
	}
	return (total_meals);
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
		printf("%ld %d %s", time, philo->id, log);
		//printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id,
			//RESET, log);
		UNLOCK(&philo->table->mtx_display);
	}
	else if (death)
	{
		usleep(1);
		LOCK(&philo->table->mtx_display);
		printf("%ld %d %s", time, philo->id, log);
		//printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id,
			//RESET, log);
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
