/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 19:16:55 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 19:16:55 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h> /// DELETE

typedef struct s_data
{
	volatile sig_atomic_t	error_state;
	volatile sig_atomic_t	client_pid;
	volatile sig_atomic_t	bit;
	volatile sig_atomic_t	state;
}	t_data;

size_t		ft_strlen(char *s);
void	print_error(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);

#endif
