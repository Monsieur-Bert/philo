/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:28:59 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 18:05:19 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

static void	routine_eat(t_philo *philo)
{
	sem_wait(philo->table->sem_forks);
	display(get_time() - philo->table->start, philo, FORK, false);
	sem_wait(philo->table->sem_forks);
	display(get_time() - philo->table->start, philo, FORK, false);
	display(get_time() - philo->table->start, philo, EAT, false);
	sem_wait(philo->table->sem_meal_access);
	philo->last_meal = get_time();
	sem_post(philo->table->sem_meal_access);
	ft_usleep(philo->table->t_to_eat, philo->table);
	sem_wait(philo->table->sem_meal_access);
	philo->nb_meals++;
	sem_post(philo->table->sem_meal_access);
	sem_post(philo->table->sem_forks);
	sem_post(philo->table->sem_forks);
}

static void	routine_think(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	time_to_think = (philo->table->t_to_die - (get_time() - philo->last_meal)
			- philo->table->t_to_eat) / 2;
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
	sem_wait(philo->table->sem_forks);
	display(get_time() - philo->table->start, philo, FORK, false);
	ft_usleep(philo->table->t_to_die, philo->table);
	sem_post(philo->table->sem_forks);
}

static void	*monitoring_philo(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->table->sem_meal_access);
		if (get_time() - philo->last_meal >= philo->table->t_to_die)
		{
			sem_post(philo->table->sem_meal_access);
			sem_post(philo->table->sem_death);
			display(get_time() - philo->table->start, philo, DIE, true);
			return (NULL);
		}
		sem_post(philo->table->sem_meal_access);
		sem_wait(philo->table->sem_meal_access);
		if (philo->nb_meals == philo->table->meal_goal)
		{
			sem_post(philo->table->sem_meal_access);
			sem_post(philo->table->sem_full);
			return (NULL);
		}
		sem_post(philo->table->sem_meal_access);
		usleep(1000);
	}
	return (NULL);
}

void	philo_process(t_philo *philo)
{
	delayed_start(philo->table->start);
	pthread_create(&philo->th_philo, NULL, &monitoring_philo, philo);
	pthread_detach(philo->th_philo);
	if (philo->table->nb_philos == 1)
	{
		lonely_philo(philo);
		return ;
	}
	while (1)
	{
		if (philo->id % 2 != 0)
			routine_think(philo, true);
		routine_eat(philo);
		display(get_time() - philo->table->start, philo, SLEEP, false);
		ft_usleep(philo->table->t_to_sleep, philo->table);
		routine_think(philo, false);
	}
}
