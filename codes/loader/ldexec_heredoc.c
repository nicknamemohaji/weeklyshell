/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldexec_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nicknamemohaji <nicknamemohaji@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 02:12:31 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/03/27 05:27:38 by nicknamemoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"

char	*ldexec_heredoc_assign_f(void);
t_bool	ldexec_heredoc(int fd, char *delim);

/*
char	*ldexec_heredoc_assign_f(void)
:return: created tmpfile's path

Tries to create tmpfile for heredoc, up to HEREDOC_MAX define in loader.h
If creation fails(== there are HEREDOC_MAX concurrent weeklyshell's
process reading heredoc), returns NULL.

Caller should free the returned pointer after use.
*/
char	*ldexec_heredoc_assign_f(void)
{
	int		tmpnum;
	char	*tmpnum_str;
	char	*tmpfile_name;

	tmpnum = 0;
	while (tmpnum++ < HEREDOC_MAX)
	{
		tmpnum_str = ft_itoa(tmpnum);
		if (tmpnum_str == NULL)
			do_exit("ldexec_heredoc_assign_f.malloc");
		tmpfile_name = ft_strjoin("/tmp/weeklyshell_heredoc_", tmpnum_str);
		if (tmpfile_name == NULL)
			do_exit("ldexec_heredoc_assign_f.malloc");
		free(tmpnum_str);
		if (access(tmpfile_name, F_OK) == -1)
		{
			tmpnum = open(tmpfile_name, O_WRONLY | O_CREAT, 0644);
			if (tmpnum < 0)
				do_exit("ldexec_heredoc_assign_f.open");
			close(tmpnum);
			return (tmpfile_name);
		}
		free(tmpfile_name);
	}
	return (NULL);
}

t_bool	ldexec_heredoc(int fd, char *delim)
{
	char				*buf;
	int					readcount;
	const int			delim_len = ft_strlen(delim);
	struct sigaction	oldacts[2];
	t_bool				ret;

	input_sighandler_setup(oldacts);
	ret = TRUE;
	while (ret == TRUE)
	{
		buf = get_next_line(STDIN_FD);
		readcount = ft_strlen(buf);
		if (g_sigint == TRUE || readcount <= 0)
			ret = FALSE;
		else if (readcount - 1 == delim_len
			&& ft_strncmp(buf, delim, delim_len) == 0)
			break ;
		if (fd != -1)
			write(fd, buf, readcount);
		free(buf);
	}
	input_sighandler_restore(oldacts);
	return (ret);
}
