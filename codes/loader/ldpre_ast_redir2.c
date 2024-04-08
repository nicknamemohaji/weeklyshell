/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldpre_ast_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyungjle <kyungjle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 18:41:08 by kyungjle          #+#    #+#             */
/*   Updated: 2024/04/08 18:06:29 by kyungjle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "types.h"
#include "utils.h"

t_bool			ldpre_ast_redir_outfile(char *filename, enum e_node_type mode);
t_bool			ldpre_ast_redir_infile(char *filename, t_ld_heredoc heredoc,
					enum e_node_type mode, t_ld_map_env *env);
static t_bool	infile_read(char *filename);
static t_bool	infile_heredoc(char *filename,
					t_ld_map_env *env, t_ld_heredoc heredoc);

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

t_bool	ldpre_ast_redir_infile(char *filename, t_ld_heredoc heredoc,
			enum e_node_type mode, t_ld_map_env *env)
{
	close(STDIN_FD);
	if (mode == EXP_PRE_RHEREDOC)
		return (infile_heredoc(filename, env, heredoc));
	else
		return (infile_read(filename));
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
					t_ld_map_env *env, t_ld_heredoc heredoc)
{
	int		fd;
	size_t	delim_len;
	t_bool	res;
	t_bool	expansion;

	res = TRUE;
	if (access(heredoc.heredoc_name, F_OK | W_OK | R_OK) != 0)
		return (ld_errno_file("ldpre_ast_redir.access", heredoc.heredoc_name));
	delim_len = ft_strlen(filename);
	filename = ldpre_param_quote_f(ft_strdup(filename), env, NULL);
	expansion = (ft_strlen(filename) == delim_len);
	fd = dup(heredoc.stdin_fd);
	if (fd < 0)
		do_exit("ldpre_ast_redir.dup");
	fd = open(heredoc.heredoc_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		do_exit("ldpre_ast_redir.open");
	res = ldexec_heredoc(fd, filename, expansion, env);
	close(fd);
	close(STDIN_FD);
	fd = open(heredoc.heredoc_name, O_RDONLY);
	if (fd < 0)
		return (ld_errno_file("ldpre_ast_redir.open", filename));
	return (res);
}
