/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:57:10 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/21 13:57:06 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

int	isredir(const char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	check_redirerr(const char **tkns)
{
	if (!tkns[0])
		return (0);
	if (isredir(tkns[0][0]) && !tkns[1])
		return (1);
	if (tkns[0][0] == '|')
		return (1);
	tkns++;
	while (*tkns)
	{
		if (((tkns[-1][0] == '<' || tkns[-1][0] == '>') && isredir(tkns[0][0]))
			|| (isredir(tkns[0][0]) && !tkns[1]))
			return (1);
		tkns++;
	}
	return (0);
}

static int	tokenstr(char **cmdline, const char *line, int numow)
{
	int	tknlen;
	int	i;
	int	j;

	i = 0;
	while (i < numow)
	{
		line += count_isspace(line);
		tknlen = process_word(line);
		cmdline[i] = ft_calloc(tknlen + 1, sizeof(char));
		if (!cmdline[i])
		{
			free_cmndline(cmdline);
			return (1);
		}
		j = 0;
		while (j < tknlen)
		{
			cmdline[i][j] = line[j];
			j++;
		}
		line += tknlen;
		i++;
	}
	return (0);
}

char	**tokenize_line(char *line)
{
	char	**ret;
	int		numow;

	numow = count_words(line);
	ret = ft_calloc(numow + 1, sizeof(char *));
	if (!ret || tokenstr(ret, line, numow))
	{
		perror("Error");
		return (NULL);
	}
	if (check_redirerr((const char **)ret))
	{
		free_cmndline(ret);
		ft_putendl_fd("Error: Parsing gone wrong near redirection.", 2);
		return (NULL);
	}
	return (ret);
}
