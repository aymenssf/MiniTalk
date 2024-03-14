/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:09:25 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/13 21:54:27 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, char character)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((character >> i) & 1)
		{
			if(kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		else
		{
			if(kill(pid, SIGUSR2) == -1)
				exit(1);
		}
		i--;
		usleep(400);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int	i;

	i = 0;
	if (ac != 3)
	{
		write(1, "ERROR: ./client [PID] [string]\n", 31);
		exit(1);
	}
	if (ft_atoi(av[1]) == 0 || !is_valid_pid(av[1]))
		exit(1);
	pid = ft_atoi(av[1]);
	while (av[2][i] != '\0')
	{
		send_signal(pid, av[2][i]);
		i++;
	}
	return (0);
}
