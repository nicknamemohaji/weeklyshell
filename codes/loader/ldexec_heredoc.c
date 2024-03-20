/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:12:31 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/19 18:56:08 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char	*ldexec_heredoc_assign(void);
t_bool	ldexec_heredoc(int fd, char *delim);

char	*ldexec_heredoc_assign(void)
{
	int		tmpnum;
	char	*tmpnum_str;
	char	*tmpfile_name;

	tmpnum = 0;
	while (tmpnum++ < 4242)
	{
		tmpnum_str = ft_itoa(tmpnum);
		if (tmpnum_str == NULL)
			do_exit("ldexec_heredoc.itoa");
		tmpfile_name = ft_strjoin("/tmp/weeklyshell_heredoc_", tmpnum_str);
		if (tmpfile_name == NULL)
			do_exit("ldexec_heredoc.strjoin");
		free(tmpnum_str);
		if (access(tmpfile_name, F_OK) == -1)
			return (tmpfile_name);
		free(tmpfile_name);
	}
	printf("cannot create temporary file(tried %d times)\n", tmpnum);
	do_exit("ldexec_heredoc.open");
	return (NULL);
}

t_bool	ldexec_heredoc(int fd, char *delim)
{
	// TODO heredoc shell variable expansion
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
		if (readcount - 1 == delim_len
			&& ft_strncmp(buf, delim, delim_len) == 0)
		{
			ret = TRUE;
			break ;
		}
		write(fd, buf, readcount);
	}
	input_sighandler_restore(oldacts);
	return (ret);
}
