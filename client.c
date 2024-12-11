/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 01:37:00 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/11 01:37:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// SIGUSR1 = 0 - SIGUSR2 = 1 
// char = 8 bit
#include <signal.h>
#include "./libft/libft.h"

void	send_requete(int pid, char *send)
{
	int	bits;
	int	c;
	int	err;

	while (*send)
	{
		c = *send++;
		bits = 8;
		while (bits--)
		{
			if (c >> bits & 1)
				err = kill(pid, SIGUSR2);
			else
				err = kill(pid, SIGUSR1);
			if (err == -1)
				exit(1);
			usleep(100);
		}
	}
	bits = 8;
	while (bits--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
}

void	end_requete(int pid)
{
	(void)pid;
	ft_putstr_fd("\nChain received\n", 1);
	exit(0);
}

int	main(int argc, char **argv)
{
	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	signal(SIGUSR2, end_requete);
	send_requete(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
