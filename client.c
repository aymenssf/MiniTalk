/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:09:25 by aassaf            #+#    #+#             */
/*   Updated: 2024/02/21 17:24:18 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
        usleep(42);
    }
}

int main(int ac, char **av)
{
    int pid;
    int i;

    i = 0;
    if(ac != 3)
    {
        printf("Usage: ./client [PID] [string]\n");
        return 1;
    }
    pid = atoi(av[1]);
    while (av[2][i] != '\0')
    {
        send_signal(pid, (unsigned char)av[2][i]);
        i++;
    }
    return 0;
}