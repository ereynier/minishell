/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jacens <jacens@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/03 14:40:00 by ereynier     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 19:05:33 by jacens      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int		check_quote2(char *line, int *i, char c)
{
	if (line[*i] == ';' && line[*i - 1] == ';' &&
	(*i < 2 || line[*i - 2] != '\\'))
		return (1);
	if (line[*i] == '<' && line[*i - 1] == '<' &&
	(*i < 2 || line[*i - 2] != '\\'))
		return (1);
	if (c)
		(*i)++;
	if ((!line[1] && line[0] == '\\') ||(line[*i] == '\\' && !line[*i + 1]))
		return (1);
	return (0);
}

static int		check_quote(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i])
	{
		c = 0;
		if (line[i] == '\'' && (i == 0 || line[i - 1] != '\\'))
			c = '\'';
		else if (line[i] == '\"' && (i == 0 || line[i - 1] != '\\'))
			c = '\"';
		if (line[i] == '\\' && line[i + 1])
			i += 2;
		else
			i++;
		while (c && (line[i] != c || line[i - 1] == '\\'))
		{
			i++;
			if (line[i] == 0)
				return (1);
		}
		if (check_quote2(line, &i, c))
			return (1);
	}
	return (0);
}

static int		check_guillemets(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') &&
		(i == 0 || line[i - 1] != '\\'))
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

static int		catch_command(char *line, t_list **command_list)
{
	int		i;
	t_tag	*command;
	char	c;

	c = 0;
	i = 0;
	while (line[i])
	{
		command = malloc(sizeof(t_tag));
		command->str = malloc(1);
		command->str[0] = 0;
		command->tag = 0;
		command->value = 0;
		if (line[i] == ';' || line[i] == '<' || line[i] == '>' ||
		line[i] == '|' || line[i] == ' ')
		{
			if (catch_command4(line, &i, &command))
				return (1);
		}
		else
		{
			if (catch_command2(line, &i, &c, &command))
				return (1);
		}
		if (*command->str)
			ft_lstadd_back(command_list ,ft_lstnew(command));
	}
	t_list *ptr = *command_list;//////////////
	while (ptr)////////////////////////
	{///////////////////////////////////////
		printf("\033[0;35m%s, %d\033[0m\n", ((t_tag *)(ptr->content))->str,////////
		((t_tag *)(ptr->content))->tag);///////////// AFFICHE LISTE CHAINEE
		ptr = ptr->next;///////////////////////
	}/////////////////////////////
	return (0);
}

int			analyse(char *line, t_list *env)
{
	t_list *command_list;

	command_list = 0;
	if (check_quote(line))
		return (1);
	if (check_guillemets(line))
		return (1);
	catch_command(line, &command_list);
	call_command(command_list, env);
	ft_lstclear(&command_list, &free);
	return (0);
}
