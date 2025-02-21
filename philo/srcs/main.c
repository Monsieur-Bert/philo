/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:50:50 by antauber          #+#    #+#             */
/*   Updated: 2025/02/21 17:45:10 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <philo.h>

//!============================ DEBUG PRINT ==================================//
// void	print_table(t_table *table)
// {
// 	dprintf(2, "NB_PHILO _______ [%d]\n", table->nb_philos);
// 	dprintf(2, "TIME_TO_DIE ____ [%zu]\n", table->time_to_die);
// 	dprintf(2, "TIME_TO_EAT ____ [%zu]\n", table->time_to_eat);
// 	dprintf(2, "TIME_TO_SLEEP __ [%zu]\n", table->time_to_sleep);
// 	dprintf(2, "(NB_MEALS) _____ [%d]\n", table->nb_meals);
// }
// void	print_philos(t_philo *philos, int max_philos)
// {
// 	int	i = 0;
// 	while (i < max_philos)
// 	{
// 		dprintf(2, "PHILO [%d]_________\n", i + 1);
// 		dprintf(2, "__ID_PHILO _______ [%d]\n", philos[i].id);
// 		dprintf(2, "__TIME_TO_DIE ____ [%zu]\n", philos[i].time_to_die);
// 		dprintf(2, "__TIME_TO_EAT ____ [%zu]\n", philos[i].time_to_eat);
// 		dprintf(2, "__TIME_TO_SLEEP __ [%zu]\n", philos[i].time_to_sleep);
// 		dprintf(2, "__(GOAL_MEALS) ___ [%d]\n", philos[i].meal_goal);
// 		dprintf(2, "__NB_MEALS _______ [%d]\n\n", philos[i].nb_meals);
// 		i++;
// 	}
// }
//!===========================================================================//

int	main(int argc, char **argv)
{
	t_table		table;

	if (parse(argc, argv, &table) == 0)
	{
		printf("%s", TABLE);
		table.simu = true;
		table.start_time = get_time();
		init_mutex(&table);
		init_philos(&table);
		start_simulation(&table);
		clean_off_the_table(&table);
	}
}
