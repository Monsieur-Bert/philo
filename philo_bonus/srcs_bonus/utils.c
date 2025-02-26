/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:13:44 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 18:00:58 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	display(time_t time, t_philo *philo, char *log, bool is_dead)
{
	if (is_dead)
	{
		// usleep(1);
		sem_wait(philo->table->sem_display);
		//printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id, RESET, log);
		printf("%zu %d %s", time, philo->id, log);
		sem_post(philo->table->sem_display);
	}
	else
	{
		sem_wait(philo->table->sem_display);
		//printf("%s%7zu ms | %sPhilo%3d%s\t%s", BLUE, time, GREEN, philo->id, RESET, log);
		printf("%zu %d %s", time, philo->id, log);
		sem_post(philo->table->sem_display);
	}
}

bool	is_simu_ok(t_table *table)
{
	bool	status;

	sem_wait(table->sem_simu);
	status = table->simu;
	sem_post(table->sem_simu);
	return (status);
}

void	clean_off_the_table(t_table *table, bool is_child)
{
	pthread_join(table->th_death, NULL);
	if (table->meal_goal > 0)
		pthread_join(table->th_full, NULL);
	free(table->philos);
	free(table->ph_pids);
	sem_close(table->sem_simu);
	sem_close(table->sem_death);
	sem_close(table->sem_full);
	sem_close(table->sem_meal_access);
	sem_close(table->sem_display);
	sem_close(table->sem_forks);
	if (!is_child)
	{
		sem_unlink("/simu");
		sem_unlink("/death");
		sem_unlink("/full");
		sem_unlink("/meal_access");
		sem_unlink("/display");
		sem_unlink("/forks");
	}
}
