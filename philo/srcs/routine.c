/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:28:59 by antauber          #+#    #+#             */
/*   Updated: 2025/02/24 16:15:53 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	philo_is_full(t_philo *philo)
{
	bool	is_full;

	is_full = false;
	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	if (philo->nb_meals == philo->table->meal_goal)
		is_full = true;
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	return (is_full);
}

static void	routine_eat(t_philo *philo)
{
	if (philo_is_full(philo))
		return ;
	LOCK(philo->l_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	LOCK(philo->r_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	display(get_time() - philo->table->start, philo, EAT, false);
	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	philo->nb_meals++;
	philo->last_meal = get_time();
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	ft_usleep(philo->table->time_to_eat, philo->table);
	UNLOCK(philo->r_fork);
	UNLOCK(philo->l_fork);
}

void	lonely_philo(t_philo *philo)
{
	LOCK(philo->l_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	ft_usleep(philo->table->time_to_die, philo->table);
	UNLOCK(philo->l_fork);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	delayed_start(philo->table->start);
	if (philo->table->nb_philos == 1)
	{
		lonely_philo(philo);
		return (NULL);
	}
	while (is_simu_ok(philo->table))
	{
		routine_eat(philo);
		display(get_time() - philo->table->start, philo, SLEEP, false);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		display(get_time() - philo->table->start, philo, THINK, false);
	}
	return (NULL);
}
