/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:06 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/14 00:37:02 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_ack(int signal)
{
	if (signal == SIGUSR1)
	{
		write(1, "Message received successfully!\n", 31);
		exit(0);
	}
	if (signal == SIGUSR2)
		exit(1);
}

void	send_char(int pid, char character)
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

void	send_string(int pid, char *string)
{
	int	i;

	i = 0;
	signal(SIGUSR2, handle_ack);
	signal(SIGUSR1, handle_ack);
	while (string[i])
	{
		send_char(pid, string[i]);
		i++;
	}
	send_char(pid, '\0');
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
	send_string(pid, av[2]);
	return (0);
}
