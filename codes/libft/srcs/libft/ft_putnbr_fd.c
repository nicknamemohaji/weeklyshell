/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 06:08:06 by kyungjle          #+#    #+#             */
/*   Updated: 2023/10/07 02:33:04 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr_fd_rec(long n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd_rec((long)n * -1, fd);
	}
	else
		ft_putnbr_fd_rec(n, fd);
}

void	ft_putnbr_fd_rec(long n, int fd)
{
	int		mod;
	char	buf;

	mod = (int)(n % 10);
	if (n >= 10)
		ft_putnbr_fd_rec(n / 10, fd);
	buf = '0' + mod;
	write(fd, &buf, 1);
}
