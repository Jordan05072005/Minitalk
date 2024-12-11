/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 02:10:00 by jguaglio          #+#    #+#             */
/*   Updated: 2024/12/11 02:10:00 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include "libft/libft.h"

void	retrieve_requete(int bit, siginfo_t *info, void *context)
{
	static pid_t			childpid = 0;
	static int				i = 0;
	static unsigned char	bits = 0;

	(void)context;
	if (!childpid)
		childpid = info->si_pid;
	bits |= (bit == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (!bits)
		{
			kill(childpid, SIGUSR2);
			childpid = 0;
			return ;
		}
		ft_putchar_fd(bits, 1);
		bits = 0;
	}
	else
		bits = bits << 1;
}

int	main(void)
{
	struct sigaction	s_sig;

	ft_putstr_fd("PID serveur : ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	s_sig.sa_sigaction = retrieve_requete;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sig, NULL);
	sigaction(SIGUSR2, &s_sig, NULL);
	while (1)
		pause();
	return (1);
}
