/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:28:59 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 09:45:35 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	routine_eat(t_philo *philo)
{
	LOCK(philo->l_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	LOCK(philo->r_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	display(get_time() - philo->table->start, philo, EAT, false);
	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	philo->last_meal = get_time();
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	ft_usleep(philo->table->t_to_eat, philo->table);
	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	philo->nb_meals++;
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	UNLOCK(philo->r_fork);
	UNLOCK(philo->l_fork);
}

static void	routine_think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	LOCK(&philo->table->mtx_meals[philo->id - 1]);
	time_to_think = (philo->table->t_to_die - (get_time() - philo->last_meal)
			- philo->table->t_to_eat) / 2;
	UNLOCK(&philo->table->mtx_meals[philo->id - 1]);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		display(get_time() - philo->table->start, philo, THINK, false);
	ft_usleep(time_to_think, philo->table);
}

static void	lonely_philo(t_philo *philo)
{
	LOCK(philo->l_fork);
	display(get_time() - philo->table->start, philo, FORK, false);
	ft_usleep(philo->table->t_to_die, philo->table);
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
		if (philo->id % 2 != 0)
			routine_think(philo, true);
		routine_eat(philo);
		display(get_time() - philo->table->start, philo, SLEEP, false);
		ft_usleep(philo->table->t_to_sleep, philo->table);
		routine_think(philo, false);
	}
	return (NULL);
}
