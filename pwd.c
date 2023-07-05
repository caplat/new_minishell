/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:46:03 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/04 17:49:49 by acaplat          ###   ########.fr       */
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