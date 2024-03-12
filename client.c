/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:09:25 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/11 20:27:49 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(int pid, unsigned char character)
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

int	main(int ac, char **av)
{
	int	pid;
	int	i;

	if (ft_isdigit(ft_atoi(av[1])) == 0)
		exit(1);
	i = 0;
	if (ac != 3)
	{
		printf("ERROR: ./client [PID] [string]\n");
		return (1);
	}
	pid = ft_atoi(av[1]);
	if (pid == -1)
		return (-1);
	while (av[2][i] != '\0')
	{
		send_signal(pid, (unsigned char)av[2][i]);
		i++;
	}
	return (0);
}
