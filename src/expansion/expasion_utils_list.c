/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expasion_utils_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcudos <marcudos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:32:02 by marcudos          #+#    #+#             */
/*   Updated: 2025/05/14 15:32:22 by marcudos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_arg_list(t_args *head)
{
	t_args *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->arg);
		free(tmp);
	}
}
