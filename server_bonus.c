/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:16 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/10 22:38:32 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handle_signal(int signal, siginfo_t *info, void *s)
{
    static unsigned char buff = 0;
    static int i = 0;
    (void)info;
    (void)s;
    if (signal == SIGUSR1)
    {
        buff = buff << 1 | 1;
        i++;
    }
    else if(signal == SIGUSR2)
    {
        buff = buff << 1;
        i++;
    }
    if (i == 8)
    {
        write(1, &buff, 1);
        i = 0;
        buff = 0;
        kill(info->si_pid, SIGUSR2);
    }
}

int main(void)
{
    printf("Server PID: %d\n", getpid());
    usleep(50);
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    while (1)
    {
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGUSR2, &sa, NULL);
        pause();
    }
}
