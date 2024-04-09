/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_redir_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:37:13 by nicknamemoh       #+#    #+#             */
/*   Updated: 2024/04/09 16:07:29 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "utils.h"
#include "input.h"
#include "types.h"

char			*ldexec_heredoc_assign_f(void);
t_bool			ldexec_heredoc(int fd, char *delim,
					t_bool expansion, t_ld_map_env *env);
static t_bool	heredoc_getline(int fd, char *delim,
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
		tmpfile_name = ft_strjoin("weeklyshell_heredoc_", tmpnum_str);
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
	struct sigaction	oldacts[2];
	struct termios		oldterm;
	t_bool				ret;

	input_sighandler_setup(oldacts);
	input_terminal_setup(&oldterm);
	g_sigint = FALSE;
	ret = heredoc_getline(fd, delim, expansion, env);
	input_sighandler_restore(oldacts);
	input_terminal_restore(&oldterm);
	if (g_sigint != TRUE)
		ret = TRUE;
	if (!ret)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	return (ret);
}

static t_bool	heredoc_getline(int fd, char *delim,
					t_bool expansion, t_ld_map_env *env)
{
	t_bool			ret;
	char			*buf;
	const size_t	delim_len = ft_strlen(delim);

	ret = TRUE;
	while (ret == TRUE)
	{
		buf = readline("heredoc > ");
		if (g_sigint == TRUE || buf == NULL)
			ret = FALSE;
		if (ret == TRUE && ft_strlen(buf) == delim_len
			&& ft_strncmp(buf, delim, delim_len) == 0)
			break ;
		if (ret == TRUE && expansion)
			buf = ldpre_param_expansion_f(buf, env);
		if (ret == TRUE)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
		}
	}
	free(buf);
	return (ret);
}
