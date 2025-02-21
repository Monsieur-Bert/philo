/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:28:59 by antauber          #+#    #+#             */
/*   Updated: 2025/02/21 17:38:33 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	routine_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		LOCK(philo->l_fork);
		status_display(get_time() - philo->table->start_time, philo, FORK, false);
		LOCK(philo->r_fork);
		status_display(get_time() - philo->table->start_time, philo, FORK, false);
	}
	else
	{
		LOCK(philo->r_fork);
		status_display(get_time() - philo->table->start_time, philo, FORK, false);
		LOCK(philo->l_fork);
		status_display(get_time() - philo->table->start_time, philo, FORK, false);;

	}
	status_display(get_time() - philo->table->start_time, philo, EAT, false);

	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	philo->nb_meals++;
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);

	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	philo->last_meal = get_time();
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->id % 2 == 0)
	{
		UNLOCK(philo->l_fork);
		UNLOCK(philo->r_fork);
	}
	else
	{
		UNLOCK(philo->r_fork);
		UNLOCK(philo->l_fork);
	}
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	delayed_start(philo->table->start_time);
	// if (philo->table->nb_philos == 1)
	// {
	// 	//handle_1_philo case
	// }
	while (is_simu_ok(philo->table))
	{
		routine_eat(philo);
		status_display(get_time() - philo->table->start_time, philo, SLEEP, false);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		status_display(get_time() - philo->table->start_time, philo, THINK, false);
	}
	return (NULL);
}
