/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 15:48:36 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 16:45:01 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void initialize(char **env,t_mini *shell)
{
	shell->env = env;
	shell->env_cpy = NULL;
	shell->line = NULL;
	shell->newline = NULL;
	shell->flag = 0;
	shell->command = NULL;
	shell->length_command = 0;
	shell->add_char = ft_calloc(1,2);
	shell->simple_command = NULL;
	shell->allpath = NULL;
	shell->exe = NULL;
	shell->arg_bis = NULL;
	shell->redir = NULL;
	shell->tab = NULL;
	shell->stdin_cpy = dup(STDIN_FILENO);
	shell->stdout_cpy = dup(STDOUT_FILENO);
}
void maj_to_min(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] = str[i] + 32;
			i++;
		}
		else
			i++;
	}
}
char *add_char(char *str,char c)
{
	char *newstr;
	int i;

	i = 0;
	newstr = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while(str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = c;
	free(str);
	return(newstr);
}
int find_length(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return(i);
}
void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
		printf("%s\n",tab[i++]);
}
void free_tab(char **tab,int length)
{
	int i;

	i = -1;
	while(++i < length)
		free((tab)[i]);
	free(tab);
}

void free_arr(char **arr)
{
	size_t i;
	
	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}