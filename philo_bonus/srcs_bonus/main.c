/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:50:50 by antauber          #+#    #+#             */
/*   Updated: 2025/02/26 17:46:27 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse(argc, argv, &table) == 0)
	{
		printf("%s", TABLE);
		table.simu = true;
		table.start = get_time() + (table.t_to_die);
		if (init_semaphores(&table) == 1)
			return (1);
		if (init_philos(&table) == 1)
			return (1);
		start_simulation(&table);
		clean_off_the_table(&table, false);
	}
}
