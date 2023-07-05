/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:10:51 by acaplat           #+#    #+#             */
/*   Updated: 2023/06/22 12:42:42:32 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void echo(char **compare)
// {
//     int i;
// 	int j;
//     int flag;
  
// 	if(!compare[1])
//         printf("\n");
// 	j = find_length(compare);
//     i = check_n(compare);
//     flag = i;
// 	// printf("j--->%d\n",j);
//     // printf("check_n--->%d\n",i);
//     // printf("compare-->%s\n",compare[i]);
//     while(compare[i])
//     {
//         if(i >= 1)
//         {
//             ft_putstr_fd(compare[i],1);
// 			if(i < j - 1)
//             	ft_putchar_fd(' ',1);
//             i++;
//         }
//     }
//     if(flag == 1)
//         ft_putchar_fd('\n',1);
// }
int check_n(char **compare)
{
    int i;
    int j;

    i = 0;
    while(compare[++i])
    {
        j = 0;
        if(compare[i][j++] == '-' && compare[i][j] && compare[i][j] == 'n')
        {
            while(compare[i][j] == 'n')
                j++;
            if(compare[i][j] && compare[i][j] != 'n')
                return(1);
        }
        else
            return i;
    }
    return(i);
}

void echo(char **compare)
{
    int i;
	int j;
    int k;
    int flag;
    int flag_bis;
  
	k = 0;
    flag_bis = 0;
	j = find_length(compare);
    i = check_n(compare);
    flag = i;
    while(compare[i])
    {
        echo_bis(compare,i,k,flag_bis);
        if(i < j - 1)
            ft_putchar_fd(' ',1);
        i++;
        k = 0;
    }
    if(flag == 1)
        ft_putchar_fd('\n',1);
}

int	cote(char c,int flag)
{
    if (c == '\"' && flag == 0)
		flag = 2;
	else if (c == '\"' && flag == 2)
		flag = 0;
	else if (c == '\'' && flag == 0)
		flag = 1;
	else if (c == '\'' && flag == 1)
		flag = 0;
    return(flag);
}
void echo_bis(char **compare,int i,int k,int flag_bis)
{
    while(compare[i][k])
        {
            if(i >= 1)
            {
                if(flag_bis == 0 && (compare[i][k] == '\'' || compare[i][k] == '\"'))
                    k++;
                flag_bis = cote(compare[i][k],flag_bis);
                ft_putchar_fd(compare[i][k],1);
            }
            k++;
        }
}
