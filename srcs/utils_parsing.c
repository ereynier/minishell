/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacens <jacens@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:40:00 by ereynier          #+#    #+#             */
/*   Updated: 2020/02/17 19:26:18 by jacens           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			catch_command4(char *line, int *i, t_tag **command)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		if (!((*command)->str = ft_append((*command)->str, &line[*i], 2)))
			return (1);
		(*command)->tag = -(int)(*command)->str[0] - 1;
		(*i) += 2;
		while (ft_iswspace(line[*i]))
			(*i)++;
	}
	else
	{
		if (!((*command)->str = ft_append((*command)->str, &line[*i], 1)))
			return (1);
		(*command)->tag = -(int)(*command)->str[0];
		(*i)++;
		while (ft_iswspace(line[*i]))
			(*i)++;
	}
	return (0);
}

static int	catch_command3(char *line, int *i, char *c, t_tag **command)
{
	while (*c || (*i > 1 && line[*i - 1] == '\\') || (line[*i] != ';' &&
	line[*i] != '<' && line[*i] != '>' && line[*i] != 0
	&& line[*i] != '|' && line[*i] != ' ' && line[*i] != '\"' &&
	line[*i] != '\''))
	{
		if (line[*i] == *c && line[*i - 1] != '\\')
		{
			*c = 0;
			(*i)++;
			break ;
		}
		if (!(*c) && line[*i] == '\\' && line[(*i) + 1] != '$')
			(*i)++;
		if (!((*command)->str = ft_append((*command)->str, &line[*i], 1)))
			return (1);
		(*i)++;
	}
	return (0);
}

int			catch_command2(char *line, int *i, char *c, t_tag **command)
{
	if (line[*i] == '\'' && (*i == 0 || line[*i - 1] != '\\'))
	{
		*c = '\'';
		(*command)->tag = 39;
		(*i)++;
	}
	else if (line[*i] == '\"' && (*i == 0 || line[*i - 1] != '\\'))
	{
		*c = '\"';
		(*command)->tag = 34;
		(*i)++;
	}
	return (catch_command3(line, i, c, command));
}

int			check_pipe(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && (i == 0 || line[i - 1] != '\\'))
		{
			j = i + 1;
			while (line[j] && ft_iswspace(line[j]))
				j++;
			if (!line[j] || line[j] == '\n' || line[j] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

int			catch_command_norme(char *line, int *i, char *c, t_tag **command)
{
	if (line[*i] == ';' || line[*i] == '<' || line[*i] == '>' ||
		line[*i] == '|' || line[*i] == ' ')
	{
		if (catch_command4(line, i, command))
			return (1);
	}
	else
	{
		if (catch_command2(line, i, c, command))
			return (1);
	}
	return (0);
}
