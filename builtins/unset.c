/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:28:12 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 12:18:45 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(t_mini *shell)
{
	int i;
	int length;
	int res;
	int res_bis;
	t_lex *current;

	current = shell->args;
	i = 1;
	while(current)
	{
		shell->tab = ft_split(current->str,' ');
		length = find_length(shell->tab);
		if(ft_strncmp(shell->tab[0],"unset",6) == 0 && length > 1)
		{
			printf("allo\n");
			while(shell->tab[i])
			{
				res = check_dup_env(shell->env,shell->tab[i]);
				res_bis = check_dup(shell->env_cpy,shell->tab[i]);
				printf("res --> %d\nres_bis --> %d\n",res,res_bis);
				if(res >= 0)
				{	
					remove_str_from_tab(&shell->env,res);
				}
				if(res_bis >= 0)
					remove_str_from_tab(&shell->env_cpy,res_bis);
				i++;
			}
		}
		// free_tab(shell->tab,length);
     	current = current->next;
	}
}

