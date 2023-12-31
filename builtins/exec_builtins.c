/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:58:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/17 16:50:58 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_built_in(t_lex *current,t_mini *shell)
{
    char **compare;

        compare = ft_split(current->str,' ');
        if(ft_strncmp(compare[0],"echo",5) == 0)
        {
            echo(compare);
            exit(0);
        }
        if(ft_strncmp(compare[0],"cd",3) == 0)
        {   
            change_directory(compare[1],shell);
            exit(0);
        }
        if(ft_strncmp(compare[0],"env",4) == 0)
        {    
            print_env(shell);
            exit(0);
        }
        if(ft_strncmp(compare[0],"pwd",4) == 0)
        {   
            pwd();
            exit(0);
        }
        free(compare);
}
