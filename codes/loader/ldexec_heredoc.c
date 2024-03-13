/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:12:31 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/14 02:43:07 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "input.h"

int		ldexec_heredoc_tmpfile(void);
t_bool	ldexec_heredoc(int fd, char *delim);

int	ldexec_heredoc_tmpfile(void)
{
	int		fd;
	int		tmpnum;
	char	*tmpnum_str;
	char	*tmpfile;

	tmpnum = 0;
	while (tmpnum++ < 4242)
	{
		tmpnum_str = ft_atoi(tmpnum);
		tmpfile = ft_strjoin("/tmp/weeklyshell_heredoc_", tmpnum_str);
		free(tmpnum_str);
		fd = open(tmpfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd > 0)
			break ;
		free(tmpfile);
	}
	free(tmpfile);
	if (fd < 0)
	{
		printf("cannot create temporary file(tried %d times)\n", tmpnum);
		do_exit("ldexec_heredoc.open");
	}
	return (fd);
}

t_bool	ldexec_heredoc(int fd, char *delim)
{
	char				buf[100];
	int					readcount;
	const int			delim_len = ft_strlen(delim);
	struct sigaction	oldacts[2];
	t_bool				ret;

	input_sighandler_setup(oldacts);
	while (1)
	{
		readcount = read(STDIN_FD, buf, 100);
		if (g_sigint == TRUE || readcount <= 0)
		{
			ret = FALSE;
			break ;
		}
		if (ft_strncmp(&buf, delim, delim_len) == 0)
		{
			ret = TRUE;
			break ;
		}
		write(fd, buf, readcount);
	}
	input_sighandler_restore(oldacts);
	return (ret);
}
