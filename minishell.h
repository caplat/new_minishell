/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:58 by acaplat           #+#    #+#             */
/*   Updated: 2023/06/30 17:34:00 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_lex
{
	char			*str;
	struct s_lex	*next;
	struct s_lex	*prev;
	struct s_lex	*sublist;
}					t_lex;

typedef struct s_mini
{
	char			**env;
	char			*line;
	char			*newline;
	int				flag;
	char			**command;
	int				length_command;
	char			*add_char;
	char			**simple_command;
}					t_mini;

typedef struct s_compteur
{
	int				i;
	int				j;
	int				length;
}					t_compteur;

typedef struct s_elem
{
	char			data;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

//Main

void				minishell_loop(t_mini *shell);

//Utils

void				initialize(char **env, t_mini *shell);
void				maj_to_min(char *str);
char				*add_char(char *str, char c);
int					find_length(char **str);

//Signal

void				do_signal(void);
void				handle_SIGINT(int signal);
void				handle_SIGQUIT(int signal);

//Parsing

int					count_quotes(char *line);
int					find_matching_quote(char *line, int i, int *nb_del,
						int del);
t_elem				*get_my_list(t_mini *shell);
void				separate_command(t_elem *lst, t_mini *shell);

//dollar

void				replace_line(char *line, t_mini *shell);
void				set_flag(char *line, t_mini *shell, int i);
char				*compare_line(char *line, int i);
int					compare_with_env(char *compare, t_mini *shell);

// Linked_list

void				add_element(t_elem **head, char data);
void				printlist(t_elem *head);
t_elem				*create_elem(char data);
void				insert_after(t_elem *lst, char newdata);
void				processlist(t_elem *head, char targetchar, char newdata);
void				processlist_chevron(t_elem *head, char targetchar,
						char newdata);
char				*convert_to_str(t_elem *head);
void				free_list(t_elem *head);

// Lexer

void				add_element_bis(t_lex **head, char *simple_command);
void				printlist_bis(t_lex *head);
void				free_list_bis(t_lex *head);
t_lex				*get_my_element(t_mini *shell);
t_lex				*set_command(t_lex *head, t_mini *shell);
int					check_flag_bis(t_lex *current, int flag);

// Token

void				tokenize(t_lex *simple_command,t_mini *shell);
t_lex *create_node(char *str);
void add_node_to_lst(t_lex **list,t_lex *newnode);
void display_sublist(t_lex *simple_command);
void args(t_lex *simple_command,t_mini *shell);

#endif