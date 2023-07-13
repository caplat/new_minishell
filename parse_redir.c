/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:08:46 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/12 15:45:26 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_redir(t_lex *simple_command, t_mini *shell)
{
	t_lex	*current;
	char	*str;

	str = NULL;
	str = ft_strjoin(str,"");
	current = simple_command;
	while (current)
	{
		if (ft_strncmp(current->str, ">", 2) == 0 |ft_strncmp(current->str,"<", 2) == 0 | ft_strncmp(current->str, ">>",3) == 0 |ft_strncmp(current->str, "<<", 3) == 0)
		{
			str = "";
			str = ft_strjoin(str, current->str);
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, current->next->str);
			add_element_bis(&shell->redir, ft_strdup(str));
			delete_node(&simple_command, current);
			current = current->next;
			delete_node(&simple_command, current);
		}
		current = current->next;
	}
	free(str);
}
