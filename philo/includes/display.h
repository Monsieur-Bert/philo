/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antauber <antauber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 10:17:16 by antauber          #+#    #+#             */
/*   Updated: 2025/02/24 13:16:44 by antauber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# define ERR_ARGS 	"error : wrong number of argument\n"
# define ERR_ARGS_L	34
# define ERR_PH 	"error : How would no philo reflect?\n"
# define ERR_PH_L	37
# define ERR_DIE	"error : How would a philo reflect if they die instantly?\n"
# define ERR_DIE_L	58
# define ERR_EAT	"error : How would a philo eat if there's no mealtime?\n"
# define ERR_EAT_L	55
# define ERR_SL		"error : How would a philo sleep if there's no bedtime?\n"
# define ERR_SL_L	56
# define ERR_MEAL	"error : How would a philo survive without eating once ?\n"
# define ERR_MEAL_L 57

# define TABLE	"============ 🍽️  PHILOSPHERS DINER 🍽️  =============\n\n"
// # define FORK	"has taken a fork\t🍴\n"
// # define EAT	"is eating\t\t🍝\n"
// # define SLEEP	"is sleeping\t\t💤\n"
// # define THINK	"is thinking\t\t🤔\n"
// # define DIE	"died\t\t\t🪦\n"

# define FORK	"has taken a fork\n"
# define EAT	"is eating\n"
# define SLEEP	"is sleeping\n"
# define THINK	"is thinking\n"
# define DIE	"died\n"

# define RESET	"\e[0m"
# define GREEN	"\e[0;32m"
# define BLUE	"\e[0;34m"

#endif