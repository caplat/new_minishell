/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 17:34:50 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 17:17:29 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	*shell;

	(void)argv;
	if (argc != 1)
	{
		printf("retry without arguments\n");
		exit(0);
	}
	shell = malloc(sizeof(t_mini));
	initialize(env, shell);
	shell->env_cpy = do_export(shell);
	// rl_catch_signals = 0;
	do_signal();
	minishell_loop(shell);
}
void	minishell_loop(t_mini *shell)
{
	t_elem *lst;
	t_lex *simple_command;
	
	while(1)
	{
		shell->line = readline(">>");
		if(shell->line)
		{
			if(ft_strlen(shell->line) > 0)
			{
				add_history(shell->line);
				if(count_quotes(shell->line) == 1)
				{
					replace_line(shell->line,shell);
					lst = get_my_list(shell);
					separate_command(lst,shell);
					shell->newline = convert_to_str(lst);
					simple_command = get_my_element(shell);
					parse_redir(&simple_command,shell);
					printf("\nsimple_command :\n");
					printlist_bis(simple_command);
					printf("\nshell->redir :\n");
					printlist_bis(shell->redir);
					printf("\n\n");
					shell->args = set_command(simple_command,shell);
					export(shell);
					unset(shell);
					cd(shell);
					exec_env(shell);
					check_redir(shell);
					do_the_pipe(shell);
					// tokenize(simple_command,shell);
					// args(simple_command,shell);
					// display_sublist(simple_command);
					// printf("\n");
					// printlist_bis(shell->args);
				}
				free(shell->line);
				shell->add_char = ft_calloc(1,2);
			}
		}
		else
			exit(0);
	}
}
