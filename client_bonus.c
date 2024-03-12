/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:06 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/11 20:30:07 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_ack(int signal)
{
	if (signal == SIGUSR1)
	{
		printf("Message received successfully!\n");
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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
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
	int	pid;
	int	i;

	if (ft_isdigit(ft_atoi(av[1])) == 0)
		exit(1);
	i = 0;
	if (ac != 3)
	{
		printf("ERROR: ./client_bonus [PID] [string]\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid == -1)
		return (-1);
	send_string(pid, av[2]);
	while (1)
		;
	return (0);
}
