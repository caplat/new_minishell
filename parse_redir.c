/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:08:46 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 16:30:24 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_lex **simple_command, t_mini *shell)
{
	t_lex	*current;
	t_lex	*next_node;
	t_lex	*prev_node;
	char	*redir_str;
	char	*str;

	current = *simple_command;
	str = ft_strdup("");
	free_list_bis(shell->redir);
	shell->redir = NULL;
	while (current)
	{
		next_node = current->next;
		if (next_node && (ft_strncmp(current->str, ">", 2) == 0
			|| ft_strncmp(current->str, "<", 2) == 0
			|| ft_strncmp(current->str, ">>", 3) == 0
			|| ft_strncmp(current->str, "<<", 3) == 0))
		{
			redir_str = ft_strjoin(current->str, " ");
			redir_str = ft_strjoin(redir_str, next_node->str);
			add_element_bis(&shell->redir, ft_strdup(redir_str));
			if (current == *simple_command)
				*simple_command = next_node->next;
			else
			{
				prev_node = *simple_command;
				while (prev_node && prev_node->next != current)
					prev_node = prev_node->next;
				if (prev_node)
					prev_node->next = next_node->next;
			}
			free(current->str);
			free(current);
			free(next_node->str);
			free(next_node);
			free(redir_str);
			current = next_node->next;
		}
		else
			current = next_node;
	}
	free(str);
}
