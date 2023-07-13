/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 18:28:12 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/13 15:17:06 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(t_mini *shell)
{
	int i;
	int length;
	char **tab;
	int res;
	int res_bis;

	i = 1;
	while(shell->args)
	{
		tab = ft_split(shell->args->str,' ');
		length = find_length(tab);
		if(ft_strncmp(tab[0],"unset",6) == 0 && length > 1)
		{
			while(tab[i])
			{
				res = check_dup_env(shell->env,tab[i]);
				res_bis = check_dup(shell->env_cpy,tab[i]);
				printf("%d\n%d\n",res,res_bis);
				if(res >= 0)
				{	
					remove_str_from_tab(&shell->env,res);
				}
				if(res_bis >= 0)
					remove_str_from_tab(&shell->env_cpy,res_bis);
				i++;
				printf("ERROR\n");
			}
		}
		tab = NULL;
     	shell->args = shell->args->next;
	}
	free(tab);
}
