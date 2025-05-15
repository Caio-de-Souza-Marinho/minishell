/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:04:15 by marcudos          #+#    #+#             */
/*   Updated: 2025/05/14 16:06:24 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expand_envv(t_args **args, t_env *env)
{
	t_args	*head;
	t_args	*arg;

	head = (*args);
	arg = head;

}

char	*expand_variable(char *input, t_env *env, int force_expand)
{
	char	*key;
	char	*value;
	int		i;
	int		state;
	int		start;

	i = 0;
	state = NO_QUOTE;
	while (input[i])
	{
		update_state_quote(input, &state, &i);
		i++;
		if (input[i] == '$' && (state != SINGLE_QUOTE || force_expand))
		{
			start = ++i;
			while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
				i++;
			key = ft_substr(input, start, i - start);
			if (!key)
				return (NULL);
			value = find_env_value(key, env);
			free(key);
			if (!value)
				return (ft_strdup(""));
			return (value);
		}
		i++;
	}
	return (ft_strdup(input));
}

char	*find_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->key));
		env = env->next;
	}
	return (ft_strdup(""));
}
