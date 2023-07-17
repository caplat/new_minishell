/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:46:34 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 11:39:16 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void exec_env(t_mini *shell)
{
	if(ft_strncmp(shell->tab[0],"env",4) == 0)
		print_env(shell);
}
void print_env(t_mini *shell)
{
	int i;

	i = 0;
		while(shell->env[i])
			printf("%s\n",shell->env[i++]);
}

void env_cpy(t_mini *shell)
{
	int i;

	i = 0;
	shell->env_cpy = malloc(sizeof(char *) * (find_length(shell->env) + 1));
	while(shell->env[i])
	{
		shell->env_cpy[i] = ft_strdup(shell->env[i]);
		i++;
	}
}
