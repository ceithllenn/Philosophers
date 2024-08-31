/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elvallet <elvallet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 07:10:42 by elvallet          #+#    #+#             */
/*   Updated: 2024/08/31 11:18:35 by elvallet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

void	ft_putstr(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	is_n(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		else
			i++;
	}
	return (1);
}

int	check_arguments(char **argv)
{
	if (!is_n(argv[1]) || !ft_atoi(argv[1]))
		return (ft_putstr("Wrong number of philosophers\n", 2), 0);
	else if (!is_n(argv[2]) || !ft_atoi(argv[2]))
		return (ft_putstr("Wrong time to die\n", 2), 0);
	else if (!is_n(argv[3]) || !ft_atoi(argv[3]))
		return (ft_putstr("Wrong time to eat\n", 2), 0);
	else if (!is_n(argv[4]) || !ft_atoi(argv[4]))
		return (ft_putstr("Wrong time to sleep\n", 2), 0);
	else if (argv[5] && (!is_n(argv[5]) || !ft_atoi(argv[5])))
		return (ft_putstr("Wrong number of meals to eat\n", 2), 0);
	return (1);
}
