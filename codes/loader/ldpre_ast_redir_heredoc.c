/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_redir_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:37:13 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/04 19:13:18 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"
#include "types.h"

char	*ldexec_heredoc_assign_f(void);
t_bool	ldexec_heredoc(int fd, char *delim,
			t_bool expansion, t_ld_map_env *env);

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

t_bool	ldexec_heredoc(int fd, char *delim,
			t_bool expansion, t_ld_map_env *env)
{
	char				*buf;
	struct sigaction	oldacts[2];
	t_bool				ret;

	input_sighandler_setup(oldacts);
	ret = TRUE;
	while (ret == TRUE)
	{
		// TODO ctrl c 입력시 입력 버퍼에 남아있던 부분들이 출력되는 문제 해결
		// TODO EOF 입력시 이상하게 출력됨
		write(2, "heredoc > ", 10);
		buf = get_next_line(STDIN_FD);
		rl_on_new_line();
		if (g_sigint == TRUE || buf == NULL || *buf == '\0')
			ret = FALSE;
		if (ret == TRUE && ft_strlen(buf) - 1 == ft_strlen(delim)
			&& ft_strncmp(buf, delim, ft_strlen(delim)) == 0)
		{
			free(buf);
			break ;
		}
		if (ret == TRUE && expansion)
			buf = ldpre_param_expansion_f(buf, env);
		if (ret == TRUE)
			write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	input_sighandler_restore(oldacts);
	return (ret);
}
