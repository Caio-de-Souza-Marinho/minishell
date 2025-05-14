/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:43:01 by marcudos          #+#    #+#             */
/*   Updated: 2025/04/28 17:52:00 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	expander(char	***args, t_env *env)
{
	char	*expanded;
	char	*temp;
	int		i;
	t_quote	state;

	i = 0;
	while ((*args)[i])
	{
		expanded = expander_expand((*args)[i], env, &state);
;
		temp = (*args)[i];
		(*args)[i] = expanded;
		free(temp);
		i++;
	}
}

char	*expand_next_token(char *input, t_env *env, t_quote *state, int *i)
{
	char	*expanded;

	update_state_quote(input, state, i);
	printf("%d\n", *state);
	if (*state == NO_QUOTE)
		printf("EXPAND && DIVIDE\n");
	else if (*state == SINGLE_QUOTE)
		printf("NO EXPAND && NO DIVIDE\n");
	else if (*state == DOUBLE_QUOTE)
		printf("EXPAND && NO DIVIDE\n");
	if (input[*i] == '$' || input[*i] == '~')
	{
		expanded = expand_token(&input[*i], env, *state);
		(*i) += get_expand_len(&input[*i], *state);
		return (expanded);
	}
	else
	{
		expanded = ft_substr(input, *i, 1);
		(*i)++;
		return (expanded);
	}
}

char	*expander_expand(char *input, t_env *env, t_quote *state)
{
	char	*res;
	char	*temp;
	char	*next;
	// t_quote	state;
	int		i;

	if (!input)
		return (NULL);
	i = 0;
	*state = NO_QUOTE;
	res = NULL;
	while (input[i])
	{
		next = expand_next_token(input, env, state, &i);
		if (!res)
			res = ft_strdup(next);
		else
		{
			temp = res;
			res = ft_strjoin(temp, next);
			free(temp);
		}
		free(next);
	}
	return (res);
}

char	*expand_token(char *input, t_env *env, t_quote state)
{
	if (state != SINGLE_QUOTE)
	{
		if (input[0] == '$')
		{
			if (input[1] != ' ')
				return (expand_env(extract_key(&input[1]), env));
			else
				return (ft_strdup("$"));
		}
	}
	return (ft_substr(input, 0, 1));
}
