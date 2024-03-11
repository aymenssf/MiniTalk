/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:28:06 by aassaf            #+#    #+#             */
/*   Updated: 2024/03/10 22:59:34 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void handle_ack(int signal)
{
    if (signal == SIGUSR2)
        printf("Message received successfully!\n");
}

void send_signal(int pid, unsigned char character)
{
    int i;

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

int main(int ac, char **av)
{
    int pid;
    int i;

    i = 0;
    if(ac != 3)
    {
        printf("Usage: ./client_bonus [PID] [string]\n");
        return 1;
    }
    pid = atoi(av[1]);
        signal(SIGUSR2, handle_ack);
    while (av[2][i] != '\0')
    {
        signal(SIGUSR1, handle_ack);
        signal(SIGUSR2, handle_ack);
        send_signal(pid, (unsigned char)av[2][i]);
        i++;
    }
    return 0;
}
