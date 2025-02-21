/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:13:44 by antauber          #+#    #+#             */
/*   Updated: 2025/02/21 16:56:28 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	status_display(time_t time, t_philo *philo, char *log, bool death)
{
	if (is_simu_ok(philo->table) || death)
	{
		LOCK(&philo->table->mtx_display);
		printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id, RESET, log);
		UNLOCK(&philo->table->mtx_display);
	}
}


bool	is_simu_ok(t_table *table)
{
	bool	status;
	
	LOCK(&table->mtx_simu);
	status = table->simu;
	UNLOCK(&table->mtx_simu);
	return (status);
}

void	clean_off_the_table(t_table *table)
{
	int	i;

	i = 0;
	while(i < table->nb_philos)
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
