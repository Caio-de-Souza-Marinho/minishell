/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:15:50 by marcudos          #+#    #+#             */
/*   Updated: 2025/05/14 15:37:01 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_args	*create_arg_list(char **args);

void	expand(char **args)
{
	char	**new_args;
	t_args	*head;

	head = create_arg_list(args); 
}

t_args	*create_arg_list(char **args)
{
	t_args	*head;
	t_args	*arg;
	t_args	*new;
	int	i;

	if (!args || !args[0])
		return (NULL);
	head = (t_args *) malloc(sizeof(t_args));
	if (!head)
		return (NULL);
	head->arg = ft_strdup(args[0]);
	head->next = NULL;
	arg = head;
	i = 1;
	while (args[i])
	{
		new = (t_args *) malloc(sizeof(t_args));
		if (!new)
			return (free_arg_list(head), NULL);
		new->arg = ft_strdup(args[i]);
		new->next = NULL;
		arg->next = new;
		arg = arg->next;
		i++;
	}
	return (head);
}
