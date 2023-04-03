/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexingutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:12:17 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/20 11:29:39 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

int	count_isspace(const char *line)
{
	int	ret;

	ret = 0;
	while (ft_isspace(line[ret]))
		ret++;
	return (ret);
}

int	handle_quotes(const char *line, const char flag)
{
	int	ret;

	ret = 1;
	while (line[ret] != flag && line[ret])
		ret++;
	if (!line[ret])
		return (0);
	return (ret);
}

int	handle_redir(const char *line)
{
	if (*line == '<' || *line == '>')
		if (line[1] == line[0])
			return (2);
	return (1);
}

int	process_word(const char *line)
{
	int	ret;

	ret = 0;
	if (isredir(*line))
	{
		ret += handle_redir(line);
		return (ret);
	}
	while (line[ret] && !ft_isspace(line[ret]) && !isredir(line[ret]))
	{
		if (line[ret] == '\'' || line[ret] == '\"')
			ret += handle_quotes(&line[ret], line[ret]);
		ret++;
	}
	return (ret);
}

int	count_words(const char *line)
{
	int	numow;

	if (!line)
		return (0);
	numow = 0;
	line += count_isspace(line);
	while (*line)
	{
		line += process_word(line);
		line += count_isspace(line);
		numow++;
	}
	return (numow);
}
