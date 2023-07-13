/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:46:03 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/13 13:09:59 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void pwd()
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if(cwd == NULL)
	{
		perror("error current directory");
		return;
	}
	printf("%s\n",cwd);
	free(cwd);
}