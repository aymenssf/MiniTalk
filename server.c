/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:09:38 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/11 20:26:45 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal)
{
	static unsigned char	buff = 0;
	static int				i = 0;

	if (signal == SIGUSR1)
	{
		buff = buff << 1 | 1;
		i++;
	}
	else if (signal == SIGUSR2)
	{
		buff = buff << 1;
		i++;
	}
	if (i == 8)
	{
		write(1, &buff, 1);
		i = 0;
		buff = 0;
	}
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac > 1)
		exit(1);
	printf("Server PID: %d\n", getpid());
	usleep(50);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
}
