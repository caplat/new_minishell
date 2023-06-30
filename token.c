/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:52:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/06/30 17:51:43 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokenize(t_lex *simple_command,t_mini *shell)
{
	t_lex *current;
	t_lex *redirection;

	redirection = NULL;
	current = simple_command;
	while(current)
	{
		shell->flag = check_flag_bis(current,shell->flag);
		if(shell->flag == 0 && (ft_strncmp(current->str,">",2) == 0 | ft_strncmp(current->str,">>",3) == 0 | ft_strncmp(current->str,"<",2) == 0 | ft_strncmp(current->str,"<<",3) == 0))
		{
			redirection = NULL;
			add_node_to_lst(&redirection,create_node(ft_strdup(current->str)));
			add_node_to_lst(&redirection,create_node(ft_strdup(current->next->str)));
			free(current->str);
			current->str = NULL;
			free(current->next->str);
			current->next->str = NULL;
			current->sublist = redirection;
			current = current->next;
		}
		current = current->next;
	}
}
t_lex *create_node(char *str)
{
	t_lex *newnode;

	newnode = malloc(sizeof(t_lex));
	newnode->str = str;
	newnode->next = NULL;
	newnode->prev = NULL;
	newnode->sublist = NULL;
	return(newnode);
}
void add_node_to_lst(t_lex **list,t_lex *newnode)
{
	t_lex *current;
	
	if(*list == NULL)
		*list = newnode;
	else
	{
		current  = *list;
		while(current->next != NULL)
			current = current->next;
		current->next = newnode;
		newnode->prev = current;
	}
}
void display_sublist(t_lex *simple_command)
{
	t_lex *current;
	t_lex *current_sub;

	current = simple_command;
	while(current)
	{
		printf("maillon : %s\n",current->str);
		if(current->sublist != NULL)
		{
			current_sub = current->sublist;
			printf("liste interne :\n");
			while(current_sub)
			{
				printf("%s\n",current_sub->str);
				current_sub = current_sub->next;
			}
		}
		current = current->next;
	}
}
void args(t_lex *simple_command,t_mini *shell)
{
	t_lex *current;
	t_lex *current_bis;
	t_lex *args;
	char *arg;

	current = simple_command;
	current_bis = simple_command;
	args = NULL;
	arg = ft_calloc(1,1);
	while(current)
	{
		shell->flag = check_flag_bis(current,shell->flag);
		if(shell->flag == 0 && ft_strncmp(current->str,"|",2) == 0)
		{
			while(current_bis != current)
			{
				if(current_bis->str != NULL)
				{	
					arg = ft_strjoin(arg,current_bis->str);
					arg = ft_strjoin(arg," ");
				}
				printf("arg-->%s\n",arg);
				current_bis = current_bis->next;
			}
			args = NULL;
			add_node_to_lst(&args,create_node(ft_strdup(arg)));
			current->sublist = args;
			current = current->next;
		}
		current = current->next;
	}
	free(arg);
}
