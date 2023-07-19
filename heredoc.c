/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:11:07 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/19 19:12:01 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_lex *simple_command)
{
	int		fd;
	char	*del;
	t_lex	*current;

	current = simple_command;
	fd = open(".heredoc", O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("open error");
		exit(1);
	}
	while (current)
	{
		if (ft_strncmp(current->str, "<<", 3) == 0 && current->next)
		{
			del = current->next->str;
			too_much(fd,del);
		}
		current = current->next;
	}
	close(fd);
}
void too_much(int fd,char *del)
{
	char *buffer;
	
	while(1)
	{
		buffer = readline(">");
		if(!buffer)
		{
			perror("readline error");
			too_much_bis(fd);
		}
		if(strncmp(buffer,del,ft_strlen(del) + 1) == 0)
		{
			free(buffer);
			break ;
		}
		if(write(fd,buffer,ft_strlen(buffer)) == -1)
		{
			perror("write error");
			free(buffer);
			close(fd);
			exit(1);
		}
		write(fd,"\n",1);
		free(buffer);
	}
}
void too_much_bis(int fd)
{
	close(fd);
	exit(1);
}
