/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aassaf <aassaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 09:09:38 by aassaf            #+#    #+#             */
/*   Updated: 2024/02/21 17:25:39 by aassaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void handle_signal(int signal)
{
    static unsigned char buff = 0;
    static int i = 0;

    if (signal == SIGUSR1)
        buff |= (1 << (7 - i));

    i++;
    if (i == 8)
    {
        printf("%c\n", buff);
        i = 0;
        buff = 0;
    }
}

int main(void)
{
    printf("Server PID: %d\n", getpid());

    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);

    while (1)
        pause();
}