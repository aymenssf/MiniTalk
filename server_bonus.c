/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:16 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/14 04:15:48 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signal, siginfo_t *info, void *s)
{
	static unsigned char	buff = 0;
	static int				i = 0;
	int						pid;

	pid = info->si_pid;
	(void)s;
	if (signal == SIGUSR1)
		buff = buff << 1 | 1;
	else if (signal == SIGUSR2)
		buff = buff << 1 | 0;
	i++;
	if (i == 8)
	{
		write(1, &buff, 1);
		if (buff == '\0')
		{
			if(kill(pid, SIGUSR1) == -1)
				exit(1);
		}
		i = 0;
		buff = 0;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sa;

	(void)av;
	if (ac > 1)
		exit(1);
	write(1, "Server PID: ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	usleep(50);
	sa.sa_sigaction = handle_signal;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL)
		== -1)
		return (-1);
	while (1)
		pause();
}
