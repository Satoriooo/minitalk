/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shirose <shirose@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:12:07 by shirose           #+#    #+#             */
/*   Updated: 2026/04/15 19:09:42 by shirose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINITALK_H
# define MINITALK_H

#define _POSIX_C_SOURCE 200809L // DELETE ME!
#include <stdio.h> // DELETE ME!
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int 	ft_strlen(char *s);
void	print_error(char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

# define SLEEP_TIME 100

#endif