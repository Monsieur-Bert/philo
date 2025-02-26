/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:57:46 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 16:04:42 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

void	delayed_start(time_t time)
{
	while (get_time() < time)
		continue ;
}

void	ft_usleep(time_t target, t_table *table)
{
	time_t	start;
	(void)table;
	start = get_time();
	while (get_time() < target + start)
	{
		if (!is_simu_ok(table))
			return ;
		usleep(10);
	}
}

time_t	get_time(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return (curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000);
}
