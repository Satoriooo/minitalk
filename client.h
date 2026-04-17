/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:27:15 by shirose           #+#    #+#             */
/*   Updated: 2026/04/18 00:21:14 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

#define _DEFAULT_SOURCE
#define _POSIX_C_SOURCE 200809L // DELETE ME!
#include <stdio.h> // DELETE ME!
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t g_state = 0;

int 	ft_strlen(char *s);
void	print_error(char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

# define SLEEP_TIME 100

#endif