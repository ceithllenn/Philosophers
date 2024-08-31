/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 07:48:01 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/29 14:05:02 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (printf("Wrong number of arguments\n"), 0);
	if (!check_arguments(argv))
		return (0);
	init(argv);
	return (0);
}
