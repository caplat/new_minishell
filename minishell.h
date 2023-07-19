/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:08:58 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/19 19:10:51 by acaplat          ###   ########.fr       */
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
	char			**env_cpy;
	char			*line;
	char			*newline;
	int				flag;
	char			**command;
	int				length_command;
	char			*add_char;
	char			**simple_command;
	char			**allpath;
	char			*exe;
	char			**arg_bis;
	t_lex			*args;
	t_lex			*redir;
	char			**tab;
	int				stdout_cpy;
	int				stdin_cpy;
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
void				print_tab(char **tab);
void				free_tab(char **tab, int length);
void				free_arr(char **arr);

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
void				delete_node(t_lex **head, t_lex *node_to_del);

// Lexer

void				add_element_bis(t_lex **head, char *simple_command);
void				printlist_bis(t_lex *head);
void				free_list_bis(t_lex *head);
t_lex				*get_my_element(t_mini *shell);
t_lex				*set_command(t_lex *head, t_mini *shell);
int					check_flag_bis(t_lex *current, int flag);

//Token

void				tokenize(t_lex *simple_command, t_mini *shell);
t_lex				*create_node(char *str);
void				add_node_to_lst(t_lex **list, t_lex *newnode);
void				display_sublist(t_lex *simple_command);
void				args(t_lex *simple_command, t_mini *shell);

//Built_in

void				check_built_in(t_lex *current, t_mini *shell);

//Echo

void				echo(char **compare);
int					check_n(char **compare);
int					cote(char c, int flag);
void				echo_bis(char **compare, int i, int k, int flag_bis);

//Cd

void				cd(t_mini *shell);
void				change_directory(char *dir, t_mini *shell);
void				change_env(char *cwd, t_mini *shell);

//Pwd

void				pwd(void);
void				too_much_line(char **dir, char **path, char **cwd);

//Env

void				exec_env(t_mini *shell);
void				print_env(t_mini *shell);
void				env_cpy(t_mini *shell);

//Export

void				sort_tab(char **tab);
void				swap_strings(char **str1, char **str2);
int					compare_length(char *str1, char *str2);
char				**do_export(t_mini *shell);
void				declare_x(char **env_cpy);
void				insert_char(char *str, char character, int position);
void				add_quotes(char **env_cpy);
int					find_character(char *str, char c);
void				export(t_mini *shell);

//Unset
void				unset(t_mini *shell);

//Add_var_export

void				add_var_export(char *str, t_mini *shell);
void				add_var_env(char *str, t_mini *shell);
int					check_dup(char **tab, char *compare);
int					check_dup_env(char **tab, char *compare);
void				add_str_to_tab(char ***tab, char *str);
void				remove_str_from_tab(char ***tab, int position);

//Exit

void				ft_exit(t_mini *shell);

//Pipe

int					get_nb_node(t_lex *head);
void				do_the_pipe(t_mini *shell);

//Exec

void				exec_all(t_mini *shell, int i);
t_lex				*find_node(int i, t_mini *shell);
void				get_my_path(t_mini *shell);
int					verify(t_mini *shell, int j);
int					execute(t_mini *shell);

//Parse_redir

void				parse_redir(t_lex **simple_command, t_mini *shell);

//Redirection

void				redir_input(char *file, t_mini *shell);
void				redir_output(char *file, t_mini *shell);
void				check_redir(t_mini *shell);

//here_doc

void				here_doc(t_lex *simple_command);
void				too_much(int fd, char *del);
void				too_much_bis(int fd);

#endif