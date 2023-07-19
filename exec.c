/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:45:00 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/18 16:18:59 by acaplat          ###   ########.fr       */
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
int verify(t_mini *shell,int j)
{
	int i;
	t_lex *current;
	char *path_part;

	i = 0;
	current = find_node(j,shell);
	// maj_to_min(current->str);
	// check_built_in(current,shell);
	shell->arg_bis = ft_split(current->str,' ');
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

t_lex *find_node(int i,t_mini *shell)
{
	int j;
	t_lex *current;

	current = shell->args;
	j = 0;
	while(j < i)
	{
		current = current->next;
		j++;
	}
	return(current);
}

void exec_all(t_mini *shell,int i)
{
	get_my_path(shell);
	verify(shell,i);
	execute(shell);
}