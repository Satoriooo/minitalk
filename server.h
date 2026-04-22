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

# define _DEFAULT_SOURCE
# define _POSIX_C_SOURCE 200809L
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	volatile sig_atomic_t	error_state;
	volatile sig_atomic_t	client_pid;
	volatile sig_atomic_t	pid_occupied;
	volatile sig_atomic_t	bit;
	volatile sig_atomic_t	busy;
}	t_data;

extern t_data	g_data;

typedef struct s_data
{
	volatile sig_atomic_t	error_state;
	volatile sig_atomic_t	client_pid;
	volatile sig_atomic_t	pid_occupied;
	volatile sig_atomic_t	bit;
	volatile sig_atomic_t	busy;
}	t_data;

static t_data	g_data;

size_t	ft_strlen(char *s);
void	print_error(char *s);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	exit_error(char *msg);
char	bits_to_char(int signum);
size_t	get_strlen(int i);
void	reset_client_state(size_t *i, size_t *idx, size_t *len, char **s);
void	signal_handler(int signum, siginfo_t *info, void *context);
void	sigaction_setup(struct sigaction *sa);
void	reset_struct(void);

#endif
