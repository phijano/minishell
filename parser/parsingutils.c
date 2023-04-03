/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:40:41 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/27 13:34:37 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

int	stff_aid(char **chain, const char **tkns, int *qtty)
{
	int	len;

	len = ft_strlen(*tkns) + 1;
	chain[*qtty] = ft_calloc(len, sizeof(char));
	if (!chain[*qtty])
		return (1);
	ft_strlcpy(chain[*qtty], *tkns, len);
	(*qtty)++;
	return (0);
}

static int	valupdate(char cmpval, char c, int *num)
{
	if (c == cmpval)
		*num = 1;
	return (1);
}

void	ioflager(t_parsing *cts, const char **tokenarr)
{
	int	cm;
	int	in;
	int	ou;

	cm = 0;
	in = 0;
	ou = 0;
	while (*tokenarr)
	{
		if (**tokenarr == '|')
		{
			cm++;
			in = 0;
			ou = 0;
		}
		else if (tokenarr[0][0] == '<')
			in += valupdate('<', tokenarr[0][1], &cts[cm].iflgs[in]);
		else if (tokenarr[0][0] == '>')
			ou += valupdate('>', tokenarr[0][1], &cts[cm].oflgs[ou]);
		tokenarr++;
	}
}

void	set_tablelast(t_parsing *cts, const int i)
{
	cts[i].cmndtable = NULL;
	cts[i].ins = NULL;
	cts[i].outs = NULL;
	cts[i].islast = 1;
}
