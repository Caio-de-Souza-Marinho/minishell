/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_operators.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:44:29 by caide-so          #+#    #+#             */
/*   Updated: 2025/04/25 15:57:59 by caide-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_two_char_op(char *input, t_token_type *type, int *len);
static int	is_one_char_op_1(char input, t_token_type *type, int *len);
static int	is_one_char_op_2(char input, t_token_type *type);

int	handle_operators(char *input, int *i, t_token_list *tokens)
{
	int				len;
	char			*value;
	t_token			*token;
	t_token_type	type;

	if (!in("()&|<>", input[*i]))
		return (0);
	if (is_two_char_op(input + *i, &type, &len)
		|| is_one_char_op_1(input[*i], &type, &len))
	{
		value = ft_substr(input, *i, len);
		if (!value)
			exit_perror("ft_substr");
		token = new_token(type, value);
		if (!token)
		{
			free(value);
			exit_perror("new_token");
		}
		token_list_append(tokens, token);
		*i += len;
		return (1);
	}
	return (0);
}

static int	is_two_char_op(char *input, t_token_type *type, int *len)
{
	*len = 2;
	if (input[0] == '>' && input[1] == '>')
	{
		*type = TOKEN_REDIR_APPEND;
		return (1);
	}
	else if (input[0] == '<' && input[1] == '<')
	{
		*type = TOKEN_HEREDOC;
		return (1);
	}
	else if (input[0] == '&' && input[1] == '&')
	{
		*type = TOKEN_LOGICAL_AND;
		return (1);
	}
	else if (input[0] == '|' && input[1] == '|')
	{
		*type = TOKEN_LOGICAL_OR;
		return (1);
	}
	return (0);
}

static int	is_one_char_op_1(char input, t_token_type *type, int *len)
{
	*len = 1;
	if (input == '>')
	{
		*type = TOKEN_REDIR_OUT;
		return (1);
	}
	else if (input == '<')
	{
		*type = TOKEN_REDIR_IN;
		return (1);
	}
	else if (input == '|')
	{
		*type = TOKEN_PIPE;
		return (1);
	}
	return (is_one_char_op_2(input, type));
}

static int	is_one_char_op_2(char input, t_token_type *type)
{
	if (input == '(')
	{
		*type = TOKEN_PAREN_OPEN;
		return (1);
	}
	else if (input == ')')
	{
		*type = TOKEN_PAREN_CLOSE;
		return (1);
	}
	return (0);
}
