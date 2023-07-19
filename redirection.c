/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:18:22 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/19 19:11:38 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_output(char *file, t_mini *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	// dup2(shell->stdout_cpy,STDOUT_FILENO);
}
void	redir_output_append(char *file, t_mini *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	// dup2(shell->stdout_cpy,STDOUT_FILENO);
}

void	redir_input(char *file, t_mini *shell)
{
	int	fd;

	(void)shell;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	// dup2(shell->stdin_cpy, STDIN_FILENO);
}

void	check_redir(t_mini *shell)
{
	char	**tab;
	t_lex	*current;

	current = shell->redir;
	while (current)
	{
		tab = ft_split(current->str, ' ');
		if (ft_strncmp(tab[0], ">", 2) == 0)
		{
			if (tab[1])
				redir_output(tab[1], shell);
			else
				perror("arg manquant pour >");
		}
		else if (ft_strncmp(tab[0], "<", 2) == 0)
		{
			if (tab[1])
				redir_input(tab[1], shell);
			else
				perror("arg manquant pour <");
		}
		else if (ft_strncmp(tab[0], ">>", 3) == 0)
		{
			if (tab[1])
				redir_output_append(tab[1], shell);
			else
				perror("arg manquant pour >>");
		}
		free_arr(tab);
		current = current->next;
	}
}

