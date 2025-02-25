/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 08:50:50 by antauber          #+#    #+#             */
/*   Updated: 2025/02/25 09:38:00 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (parse(argc, argv, &table) == 0)
	{
		printf("%s", TABLE);
		table.simu = true;
		table.start = get_time() + (table.t_to_die);
		init_mutex(&table);
		init_philos(&table);
		start_simulation(&table);
		clean_off_the_table(&table);
	}
}
