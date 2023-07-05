/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:00 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/03 16:17:06 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_my_path(t_mini *shell)
{
	int i;

	i = 0;
	while(shell->env[i])
	{
		if (ft_strncmp("PATH", shell->env[i], 4) == 0)
		{
			shell->allpath = ft_split(ft_substr(shell->env[i], 5,
				ft_strlen(shell->env[i]) - 5), ':');
			break;
		}
		else
			i++;
	}
}
int verify(t_mini *shell,int j,t_lex *simple_command)
{
	int i;
	t_lex *current;
	char *path_part;

	i = 0;
	current = find_node(j,simple_command);
	maj_to_min(current->sublist->str);
	// check_built_in(current);
	printf("sublist --> %s\n",current->sublist->str);
	shell->arg_bis = ft_split(current->sublist->str,' ');
	// printf("%d\n",j);
	while(shell->allpath[i++])
	{
		path_part = ft_strjoin(shell->allpath[i],"/");
		shell->exe = ft_strjoin(path_part,shell->arg_bis[0]);
		// printf("--%s\n",current->str);
		// printf("%s\n",shell->exe);
		free(path_part);
		if(access(shell->exe,F_OK | X_OK) == 0)
			return(1);
		free(shell->exe);
	}
	exit(printf("problem with verify\n"));
}
int execute(t_mini *shell)
{
	// printf("error\n");
	if(execve(shell->exe,shell->arg_bis,shell->env) == -1)
		exit(printf("problem with execve\n"));
	return(0);
}

t_lex *find_node(int i,t_lex *simple_command)
{
	int j;
	t_lex *current;

	current = simple_command;
	j = -1;
	while(current)
	{
		if(ft_strncmp(current->str,"|",2) == 0 && current->sublist != NULL)
		{
			j++;
			if(j == i)
				return(current);
			current = current->next;
		}
		current = current->next;
	}
	return(current);
}

void exec_all(t_mini *shell,int i,t_lex *simple_command)
{
	get_my_path(shell);
	verify(shell,i,simple_command);
	execute(shell);
}