/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:04:20 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/19 16:17:43 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void sort_tab(char **tab)
{
	int length;
	int i;
	int j;
	int n;
	int sign;

	length = find_length(tab);
	i = 0;
	j = 0;
	while(j < length - 1 && tab[i] && tab[i + 1])
	{
		while(tab[i])
		{
			if(tab[i] && tab[i + 1])
			{
				n = compare_length(tab[i],tab[i + 1]);
				sign = ft_strncmp(tab[i],tab[i + 1],n);
				if(sign > 0)
				swap_strings(&tab[i],&tab[i + 1]);
			}
			i++;
		}
		i = 0;
		j++;
	}
}
void swap_strings(char **str1,char **str2)
{
	char *temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

int compare_length(char *str1,char *str2)
{
	int n1;
	int n2;

	n1 = ft_strlen(str1);
	n2 = ft_strlen(str2);
	if(n1 <= n2)
		return n1;
	else
		return n2;
}
void declare_x(char **env_cpy)
{
	int i;

	i = 0;
	while(env_cpy[i])
	{
		env_cpy[i] = ft_strjoin("declare -x ",env_cpy[i]);
		i++;
	}

}
void insert_char(char *str, char character, int position) 
{
	int length = strlen(str);
    
    ft_memmove(str + position + 1, str + position, length - position + 1);
    str[position] = character;
}

int find_character(char *str,char c)
{
	char *found;

	found = ft_strchr(str,c);
	if(found != NULL)
		return(int)(found - str);
	return(-1);
}

void add_quotes(char **env_cpy)
{
	int i;
	int pos;

	i = 0;
	while(env_cpy[i])
	{
		pos = find_character(env_cpy[i],'=');
		if(pos != -1)
		{	
			insert_char(env_cpy[i],'\"',pos + 1);
			env_cpy[i] = ft_strjoin(env_cpy[i],"\"");
		}
		i++;
	}
}

char **do_export(t_mini *shell)
{
	env_cpy(shell);
	sort_tab(shell->env_cpy);
	declare_x(shell->env_cpy);
	add_quotes(shell->env_cpy);
	return(shell->env_cpy);
}
void export(t_mini *shell)
{
	int length;
	t_lex *current;
	int i;

	current = shell->args;
	i = 1;
	while(current)
	{
		shell->tab = ft_split(current->str,' ');
		length = find_length(shell->tab);
		if(ft_strncmp(shell->tab[0],"export",7) == 0 && length == 1)
			print_tab(shell->env_cpy);
		else if(ft_strncmp(shell->tab[0],"export",7) == 0 && length > 1)
		{
			while(shell->tab[i])
			{
				add_var_export(shell->tab[i],shell);
				add_var_env(shell->tab[i],shell);
				i++;
			}
		}
		shell->tab = NULL;
		current = current->next;
	}
	// free(tab);
	// printf("\n\n");
	// print_tab(shell->env);
}
