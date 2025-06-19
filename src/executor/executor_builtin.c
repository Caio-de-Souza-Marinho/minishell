/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 19:34:09 by caide-so          #+#    #+#             */
/*   Updated: 2025/05/25 03:42:55 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Checks if the given command is a shell builtin.
// Returns 1 if cmd is a builtin and 0 otherwise.
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

// Executes a builtin command if it matches.
// 1. Dispaches the call to the appropriate builtin implementation.
// Returns the result of the builtin function.
// Returns 1 if the command is not a recognized builtin.
int	run_builtin(char **args, t_shell *shell)
{
	char	*cmd;

	cmd = args[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (builtin_echo(args));
	else if (ft_strcmp(cmd, "cd") == 0)
		return (builtin_cd(args, shell->env));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (builtin_pwd(shell->env));
	else if (ft_strcmp(cmd, "export") == 0)
		return (builtin_export(args, &shell->env));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (builtin_unset(args, &shell->env));
	else if (ft_strcmp(cmd, "env") == 0)
		return (builtin_env(shell->env));
	else
		return (1);
}
