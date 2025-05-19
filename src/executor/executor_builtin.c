/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:34:09 by caide-so          #+#    #+#             */
/*   Updated: 2025/05/19 02:45:29 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	run_builtin(char **args, t_env *env)
{
	char	*cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(args));
	/*
	else if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(args, env));
	*/
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd());
	/*
	else if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(args, envp));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(args, envp));
	*/
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(env));
	else
		return (1);
}
