/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsermain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:47:36 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/21 12:52:57 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

static int	get_ncmds(const char **tokenarr)
{
	int	ret;

	ret = 1;
	while (*tokenarr)
	{
		if (**tokenarr == '|')
			ret++;
		tokenarr++;
	}
	return (ret);
}

static int	tablecount(int *arr, const char **tkns)
{
	int	i;

	i = 0;
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	while (tkns[i] && tkns[i][0] != '|')
	{
		if (tkns[i][0] == '<' || tkns[i][0] == '>')
		{
			if (tkns[i][0] == '<')
				arr[1]++;
			else
				arr[2]++;
			i++;
		}
		else
			arr[0]++;
		i++;
	}
	if (tkns[i] && tkns[i][0] == '|')
		i++;
	return (i);
}

static int	stuff_rows(t_parsing *cts, const char **tkns, const int cmndend)
{
	int	i;
	int	qtty[3];

	i = 0;
	qtty[0] = 0;
	qtty[1] = 0;
	qtty[2] = 0;
	while (i < cmndend && tkns[i][0] != '|')
	{
		if (tkns[i][0] == '<')
		{
			if (stff_aid(cts->ins, &tkns[++i], &qtty[1]))
				return (1);
		}
		else if (tkns[i][0] == '>')
		{
			if (stff_aid(cts->outs, &tkns[++i], &qtty[2]))
				return (1);
		}
		else if (stff_aid(cts->cmndtable, &tkns[i], &qtty[0]))
			return (1);
		i++;
	}
	return (0);
}

static int	fill_tables(t_parsing *cts, const int numocmds, const char **tkns)
{
	int	i;
	int	j;
	int	arr[3];

	i = 0;
	while (i < numocmds)
	{
		j = tablecount(arr, tkns);
		cts[i].cmndtable = ft_calloc(arr[0] + 1, sizeof(char *));
		cts[i].ins = ft_calloc(arr[1] + 1, sizeof(char *));
		cts[i].outs = ft_calloc(arr[2] + 1, sizeof(char *));
		cts[i].iflgs = ft_calloc(arr[1], sizeof(int));
		cts[i].oflgs = ft_calloc(arr[2], sizeof(int));
		cts[i].islast = 0;
		if (!cts[i].cmndtable || !cts[i].ins || !cts[i].outs
			|| !cts[i].iflgs || !cts[i].oflgs || stuff_rows(&cts[i], tkns, j))
		{
			cts[i + 1].islast = 1;
			return (1);
		}
		tkns += j;
		i++;
	}
	return (0);
}

t_parsing	*parse_line(char *line)
{
	int			numocmds;
	char		**tokenarr;
	t_parsing	*cts;

	tokenarr = tokenize_line(line);
	if (!tokenarr)
		return (NULL);
	numocmds = get_ncmds((const char **)tokenarr);
	cts = malloc(sizeof(t_parsing) * (numocmds + 1));
	set_tablelast(cts, numocmds);
	if (cts)
	{
		if (fill_tables(cts, numocmds, (const char **)tokenarr)
			|| expand_quotes(cts))
		{
			perror("Error");
			free_tables(cts);
			cts = NULL;
		}
	}
	else
		perror("Error");
	ioflager(cts, (const char **)tokenarr);
	free_cmndline(tokenarr);
	return (cts);
}
