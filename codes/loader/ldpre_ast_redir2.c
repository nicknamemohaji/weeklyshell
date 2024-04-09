/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_redir2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:41:08 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/09 16:27:58 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

t_bool			ldpre_ast_redir_outfile(char *filename, enum e_node_type mode);
t_bool			ldpre_ast_redir_infile(char *filename, t_ld_heredoc *heredoc,
					enum e_node_type mode, t_ld_map_env *env);
static t_bool	infile_read(char *filename);
static t_bool	infile_heredoc(char *filename,
					t_ld_map_env *env, char *heredoc_name);

t_bool	ldpre_ast_redir_outfile(char *filename, enum e_node_type mode)
{
	int	fd;

	if (!access(filename, F_OK) && access(filename, F_OK | W_OK) != 0)
		return (ld_errno_file("ldpre_ast_redir_outfile.access", filename));
	close(STDOUT_FD);
	if (mode == EXP_IN_RWRITE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ld_errno_file("ldpre_ast_redir_outfile.open", filename));
	return (TRUE);
}

t_bool	ldpre_ast_redir_infile(char *filename, t_ld_heredoc *heredoc,
			enum e_node_type mode, t_ld_map_env *env)
{
	int	stdout_fd;
	int	ret;

	close(STDIN_FD);
	if (mode == EXP_PRE_RHEREDOC)
	{
		if (dup(heredoc->stdin_fd) < 0)
			do_exit("ldpre_ast_redir.dup");
		stdout_fd = dup(STDOUT_FD);
		if (stdout_fd < 0)
			do_exit("ldpre_ast_redir.dup");
		close(STDOUT_FD);
		if (dup(heredoc->stdout_fd) < 0)
			do_exit("ldpre_ast_redir.dup");
		if (!heredoc->phd_name_vec->push_back(heredoc->phd_name_vec, NULL))
			do_exit("ldpre_ast_redir.heredoc");
		ret = infile_heredoc(filename, env,
				*(char **)(heredoc->phd_name_vec->back(heredoc->phd_name_vec)));
		close(STDOUT_FD);
		if (dup(stdout_fd) < 0)
			do_exit("ldpre_ast_redir.dup");
	}
	else
		ret = infile_read(filename);
	return (ret);
}

static t_bool	infile_read(char *filename)
{
	int		fd;
	t_bool	res;

	res = TRUE;
	if (access(filename, F_OK) && access(filename, F_OK | R_OK) != 0)
		return (ld_errno_file("ldpre_ast_redir.access", filename));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ld_errno_file("ldpre_ast_redir.open", filename));
	return (res);
}

static t_bool	infile_heredoc(char *filename,
					t_ld_map_env *env, char *heredoc_name)
{
	int		fd;
	size_t	delim_len;
	t_bool	res;
	t_bool	expansion;

	res = TRUE;
	if (access(heredoc_name, F_OK | W_OK | R_OK) != 0)
		return (ld_errno_file("ldpre_ast_redir.access", heredoc_name));
	delim_len = ft_strlen(filename);
	filename = ldpre_param_quote_f(ft_strdup(filename), env, NULL);
	expansion = (ft_strlen(filename) == delim_len);
	fd = open(heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		do_exit("ldpre_ast_redir.open");
	res = ldexec_heredoc(fd, filename, expansion, env);
	close(fd);
	close(STDIN_FD);
	fd = open(heredoc_name, O_RDONLY);
	if (fd < 0)
		return (ld_errno_file("ldpre_ast_redir.open", filename));
	return (res);
}
