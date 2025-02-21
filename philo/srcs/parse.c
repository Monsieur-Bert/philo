/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:03:36 by antauber          #+#    #+#             */
/*   Updated: 2025/02/21 11:38:57 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static bool	ft_isspace(int c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static size_t	ft_atoi(char *str)
{
	size_t	nb;

	nb = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		nb = nb * 10 + (*str - '0');
		str++;
	}
	if (nb >= 2147483647)
		nb = 0;
	return (nb);
}

int	parse(int argc, char **argv, t_table *table)
{
	if (argc < 5 || argc > 6)
		return (write(2, ERR_ARGS, ERR_ARGS_L));
	table->nb_philos = ft_atoi(argv[1]);
	if (table->nb_philos == 0)
		return (write(2, ERR_PH, ERR_PH_L));
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die == 0)
		return (write(2, ERR_DIE, ERR_DIE_L));
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat == 0)
		return (write(2, ERR_EAT, ERR_EAT_L));
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep == 0)
		return (write(2, ERR_SL, ERR_SL_L));
	if (argc == 6)
	{
		table->meal_goal = ft_atoi(argv[5]);
		if (table->meal_goal == 0)
			return (write(2, ERR_MEAL, ERR_MEAL_L));
	}
	else
		table->meal_goal = -1;
	return (0);
}
