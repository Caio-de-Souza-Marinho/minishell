/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 03:41:19 by caide-so          #+#    #+#             */
/*   Updated: 2025/05/25 03:52:24 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_unset_arg(char *arg, t_env **env);
int	is_valid_name(char *name);
int	env_unset(char *arg, t_env **env);

int	builtin_unset(char **args, t_env **env)
{
	int		status;
	int		i;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (handle_unset_arg(args[i], env))
			status = 1;
		i++;
	}
	return (status);
}

int	handle_unset_arg(char *arg, t_env **env)
{
	if (!is_valid_name(arg))
	{
		if (arg[0] == '-')
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd("': invalid option\n", STDERR_FILENO);
			ft_putstr_fd("unset: usage: unset [name ...]\n", STDERR_FILENO);
		}
		return (1);
	}
	env_unset(arg, env);
	return (0);
}

int	is_valid_name(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (name[0] == '\0')
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	env_unset(char *arg, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, arg) == 0)
		{
			if (prev == NULL)
				*env = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			if (curr->value)
				free(curr->value);
			free(curr);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
