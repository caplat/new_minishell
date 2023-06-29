/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:40:56 by acaplat           #+#    #+#             */
/*   Updated: 2023/06/09 22:53:13 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_line(char *line, t_mini *shell)
{
	t_compteur	var;
	char		*compare;

	var.i = -1;
	var.j = 0;
	var.length = 0;
	while (line[++var.i])
	{
		set_flag(line, shell, var.i);
		if (line[var.i] == '$' && (shell->flag == 0 || shell->flag == 2))
		{
			compare = compare_line(line, var.i);
			if (compare_with_env(compare, shell) == 1)
			{
				while (shell->command[1][var.j])
					shell->add_char = add_char(shell->add_char,shell->command[1][var.j++]);
				var.i += ft_strlen(shell->command[0]) + 1;
				var.j = 0;
			}
			else
				var.i += ft_strlen(compare) + 1;
			free(compare);
		}
		shell->add_char = add_char(shell->add_char, line[var.i]);
	}
}
void	set_flag(char *line, t_mini *shell, int i)
{
	if (line[i] == '\"' && shell->flag == 0)
		shell->flag = 2;
	else if (line[i] == '\"' && shell->flag == 2)
		shell->flag = 0;
	else if (line[i] == '\'' && shell->flag == 0)
		shell->flag = 1;
	else if (line[i] == '\'' && shell->flag == 1)
		shell->flag = 0;
	else if (line[i] == '$')
		return ;
	i++;
}
char	*compare_line(char *line, int i)
{
	char	*compare;
	int		length;
	int		pos;
	int		j;

	compare = NULL;
	length = 0;
	j = 0;
	i++;
	pos = i;
	while (ft_isalnum(line[i]) == 1 || line[i] == '_')
	{
		i++;
		length++;
	}
	compare = malloc(sizeof(char) * length + 1);
	while (j < length)
	{
		compare[j] = line[pos];
		j++;
		pos++;
	}
	compare[j] = 0;
	return (compare);
}
int	compare_with_env(char *compare, t_mini *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		shell->command = ft_split(shell->env[i], '=');
		shell->length_command = ft_strlen(shell->command[0]);
		if (ft_strncmp(compare, shell->command[0], shell->length_command
				+ 1) == 0)
			return (1);
		else
		{
			free(shell->command);
			i++;
		}
	}
	return (0);
}
