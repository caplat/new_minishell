/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:47:35 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/06 13:05:29 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_directory(char *dir)
{
	char *cwd;
	char *path;
	
	cwd = getcwd(NULL,0);
	path = "";
	if(cwd == NULL)
	{
		perror("error current directory");
		return;
	}
	too_much_line(&dir,&path,&cwd);
	printf("%s\n",dir);
	printf("%s\n",path);
	if(chdir(path) == 0)
	{
		cwd = getcwd(NULL,0);
		if(cwd != NULL)
			printf("current dir : %s\n",cwd);
		else
			perror("error getting dir");
	}
	else
		perror("dir not found");
	free(cwd);
	free(path);
}
void too_much_line(char **dir,char **path,char **cwd)
{
	if(*dir[0] == '/')
		*path = ft_strjoin(*path,*dir);
	else if(ft_strncmp(*dir,"~",2) == 0)
		*path = ft_strjoin(getenv("HOME"), "");
	else
	{
		*path = ft_strjoin(*path,*cwd);
		*path = ft_strjoin(*path,"/");
		*path = ft_strjoin(*path,*dir);
	}
}
