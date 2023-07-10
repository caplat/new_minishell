/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:01:07 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/06 16:36:13 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_nb_node(t_lex *head)
{
	t_lex *current;
	int i;

	i = 0;
	current = head;
	while(current)
	{
		current = current->next;
		i++;
	}
	return(i);
}
void do_the_pipe(t_mini *shell)
{
    int nb_node;
    int pipe_fd[2];
    int prev_pipe_read = 0;
	pid_t child_pid;
	int i;

	nb_node = get_nb_node(shell->args);
	i = -1;
    while(++i < nb_node) 
	{
        if (pipe(pipe_fd) == -1) 
		{
            perror("pipe error\n");
            return;
        }
        child_pid = fork();
        if (child_pid == -1) 
		{
            perror("fork error\n");
            return;
        }
        if (child_pid == 0) 
		{
            // Child process
            close(pipe_fd[0]);  // Close unused read end
            if (i > 0) 
			{
                // Connect input to previous pipe read end
                dup2(prev_pipe_read, STDIN_FILENO);
                close(prev_pipe_read);
            }
            if (i < nb_node - 1) 
			{
                // Connect output to current pipe write end
                dup2(pipe_fd[1], STDOUT_FILENO);
            }
            // Execute the command
            exec_all(shell, i);
            exit(0);  // Exit the child process
        } 
		else 
		{
            // Parent process
            close(pipe_fd[1]);  // Close unused write end
            if (i > 0) 
			{
                close(prev_pipe_read);  // Close previous pipe read end
            }
            prev_pipe_read = pipe_fd[0];  // Store the current pipe read end
        }
    }
    // Close the final pipe read end in the parent
    close(prev_pipe_read);
    // Wait for all child processes to finish
	i = -1;
    while(++i < nb_node)
        wait(NULL);
}
