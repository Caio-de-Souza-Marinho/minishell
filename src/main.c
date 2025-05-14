/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caide-so <caide-so@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:45:28 by caide-so          #+#    #+#             */
/*   Updated: 2025/05/03 18:26:50 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt(t_env *env);
void	minishell(char *input, t_env *env);
void	parser(t_token_list *tokens, t_env *env);
void	executor(t_ast *ast, t_env *env);

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	prompt(env);
	clean_all(env);
	return (0);
}

void	minishell(char *input, t_env *env)
{
	t_token_list	*tokens;

	tokens = tokenizer(input);
	if (tokens == NULL)
		return ;
	parser(tokens, env);
}

void	parser(t_token_list *tokens, t_env *env)
{
	t_ast	*ast;

	(void)env;
	if (!syntax_analysis(tokens))
		token_list_free(tokens);
	else
	{
		ast = parse_logical(&tokens->head, env);
		print_ast(ast, 0);
		executor(ast, env);
		token_list_free(tokens);
		ast_free(ast);
	}
}

// percorrer ast
// if node type = NODE COMMAND
// variable expansion
// wildcard expansion
// handle redirections
// execute builtin or fork-exec
// restore redirections
// if node type == PIPE
// create pipe
// fork left, redirect stdout
// fork right, redirect stdin
// wait and update status
// if node type == AND, OR
// execute left, test status, maybe execute right
// if node type == SUBSHELL
// fork, apply redirs, exec subtree, wait and
// update status
void	executor(t_ast *ast, t_env *env)
{
	(void)env;
	if (ast == NULL)
		return ;
	return ;
}

void	prompt(t_env *env)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input || ft_strcmp(input, "exit") == 0)
		{
			printf("exit\n");
			free(input);
			break ;
		}
		else if (input != NULL)
		{
			add_history(input);
			minishell(input, env);
			free(input);
		}
		else
			printf("Error reading input or end of file reached.\n");
	}
}
