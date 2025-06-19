/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:31:28 by caide-so          #+#    #+#             */
/*   Updated: 2025/05/14 22:38:40 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_exported(t_env *env);

// Converts environment linked list to a NULL-terminated array of strings.
// 1. Counts exported variables (those with values).
// 2. Allocates and fills array with "KEY=VALUE" strings.
// 3. Returns the array for use with execve.
// Note: Exits on malloc or ft_strjoin3 failure.
char	**env_list_to_array(t_env *env)
{
	int		count;
	int		i;
	char	**arr;
	t_env	*tmp;

	tmp = env;
	count = count_exported(env);
	arr = (char **)malloc((count + 1) * sizeof(char *));
	if (!arr)
		exit_perror("malloc");
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			arr[i] = ft_strjoin3(tmp->key, "=", tmp->value);
			if (!arr[i])
				exit_perror("ft_strjoin3");
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (arr);
}

// Counts how many environment variables are exported (have values).
int	count_exported(t_env *env)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

// Frees a NULL-terminated array of strings.
// 1. Frees each string in the array.
// 2. Frees the array pointer itself.
void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
