/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:58:35 by marcudos          #+#    #+#             */
/*   Updated: 2025/05/03 17:45:36 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_command	*make_command(t_token **token, t_env *env)
{
	t_command	*command;
	t_token		*t;
	int			arg;

	command = init_command();
	if (!command)
		return (NULL);
	command->arg_count = get_size_args(token);
	command->args = (char **) malloc(sizeof(char *) * (command->arg_count + 1));
	if (!command->args)
		return (NULL);
	t = *token;
	arg = 0;
	while (t && !is_pipe_or_logical(t))
	{
		if (t->type == WORD)
		{
			command->args[arg++] = ft_strdup(t->value);
			t = t->next;
		}
		else if (is_redirect(t))
			parse_redirect(&t, &command);
	}
	command->args[arg] = NULL;
	expander(&command->args, env);
	return ((*token) = t, command);
}

void	parse_redirect(t_token **token, t_command **command)
{
	if (!(*token)->next)
	{
		(*token) = (*token)->next;
		return ;
	}
	if ((*token)->type == REDIR_IN)
	{
		(*command)->infile = ft_strdup((*token)->next->value);
		(*token) = (*token)->next->next;
	}
	else if ((*token)->type == REDIR_OUT)
	{
		(*command)->outfile = ft_strdup((*token)->next->value);
		(*token) = (*token)->next->next;
	}
	else if ((*token)->type == REDIR_APPEND)
	{
		(*command)->appendfile = ft_strdup((*token)->next->value);
		(*token) = (*token)->next->next;
	}
	else if ((*token)->type == HEREDOC)
		parse_heredoc(token, command);
}

void	parse_heredoc(t_token **token, t_command **command)
{
	if ((*command)->heredoc == 1)
	{
		free((*command)->delimiter);
		free((*command)->heredoc_path);
	}
	(*command)->heredoc = 1;
	(*command)->delimiter = ft_strdup((*token)->next->value);
	(*command)->heredoc_path = ft_strjoin("tmp/", (*command)->delimiter);
	(*token) = (*token)->next->next;
}

t_command	*init_command(void)
{
	t_command	*command;

	command = (t_command *) malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	command->args = NULL;
	command->arg_count = 0;
	command->infile = NULL;
	command->outfile = NULL;
	command->appendfile = NULL;
	command->heredoc = 0;
	command->delimiter = NULL;
	command->heredoc_path = NULL;
	command->is_builtin = 0;
	return (command);
}
//
// char	**get_args(t_token **token, int size_args)
// {
// 	char	**args;
// 	int		i;
//
// 	args = (char **) malloc(sizeof(char *) * (size_args + 1));
// 	i = 0;
// 	if (!args)
// 		return (NULL);
// 	while (i < size_args)
// 	{
// 		args[i] = ft_strdup((*token)->value);
// 		(*token) = (*token)->next;
// 		i++;
// 	}
// 	args[i] = NULL;
// 	return (args);
// }
