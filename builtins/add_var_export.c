/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:21:13 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/13 12:110::23 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void add_var_export(char *str,t_mini *shell)
{
	int res;
	int pos;
	int new_pos;
	char *newstr;
	
	pos = find_character(str,'=');
	res = check_dup(shell->env_cpy,str);
	printf("res --> %d\n",res);
	if(res != -1)
		remove_str_from_tab(&shell->env_cpy,res);
	newstr = ft_strjoin("declare -x ",str);
	new_pos = find_character(newstr,'=');
	if(new_pos != -1 && newstr[new_pos + 1] == '\0')
	{	
		newstr = ft_strjoin(newstr,"\"");
		newstr = ft_strjoin(newstr,"\"");
	}
	else if(pos != -1)
	{
		printf("newstr --> %s\n",newstr);
		insert_char(newstr,'\"',new_pos + 1);
		newstr = ft_strjoin(newstr,"\"");
	}
	printf("newstr --> %s\n",newstr);
	add_str_to_tab(&shell->env_cpy,newstr);
	sort_tab(shell->env_cpy);
	free(newstr);
}

void add_str_to_tab(char ***tab,char *str)
{
	int length;
	char **newtab;
	int i;

	length = find_length(*tab);
	newtab = malloc(sizeof(char *) * (length + 2));
	if(!newtab)
	{
		perror("erreur allocation memoire");
		return;
	}
	i = -1;
	while(++i < length)
	{
		newtab[i] = ft_strdup((*tab)[i]);
		// free(*tab[i]);
	}
	newtab[length] = ft_strdup(str);
	newtab[length + 1] = NULL;
	// i = -1;
	// while(++i < length)
	// {
	// 	free((*tab)[i]);
	// }
	// free(*tab); //invalid free
	*tab = newtab;
}

void remove_str_from_tab(char ***tab,int position)
{
	int length;
	char **newtab;
	int i;
	int j;

	i = -1;
	j = 0;
	length = find_length(*tab);
	newtab = malloc(sizeof(char *) * (length + 1));
	if(!newtab)
	{	
		perror("erreur allocation memoire");
		return;
	}
	while(++i < length)
	{
		if(i != position)
		{
			newtab[j] = ft_strdup((*tab)[i]);
			j++;
		}	
	}
	newtab[j] = NULL;
	// free_tab(*tab,length);
	// free(*tab);
	*tab = newtab;
}

int check_dup(char **tab,char *compare)
{
	int i;
	int result;
	int pos;

	i = 0;
	pos = find_character(compare,'=');
	printf("--> pos %d\n",pos);
	while(tab[i])
	{
		if(pos != -1)
			result = ft_strncmp(tab[i] + 11, compare,pos);
		else
			result = ft_strncmp(tab[i] + 11, compare,ft_strlen(compare));
		if(result == 0)
			return(i);
		i++;
	}
	return(-1);
}
int check_dup_env(char **tab,char *compare)
{
	int i;
	int pos;
	i = -1;
	while(tab[++i])
	{
		pos = find_character(tab[i],'=');
		if(pos == -1)
			return(-2);
		if(ft_strncmp(tab[i],compare,pos) == 0)
			return(i);
	}
	return(-1);
}
void add_var_env(char *str,t_mini *shell)
{
	int res;

	if(find_character(str,'=') != -1)
	{
		res = check_dup_env(shell->env,str);
		printf("dup env --> %d\n",res);
		if(res == -2)
			return;
		if(res != -1)
		{	
			remove_str_from_tab(&shell->env,res);
		}
		add_str_to_tab(&shell->env,str);
	}
}