/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:58:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/04 16:17:16 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_built_in(t_lex *current)
{
    char **compare;

        compare = ft_split(current->str,' ');
        if(ft_strncmp(compare[0],"echo",5) == 0)
        {
            // printf("built_in\n");
            echo(compare);
            free(compare);
            exit(0);
        }
}
