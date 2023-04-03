/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:53:19 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/21 16:17:50 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

static void	dollarcpy(char **ogline, char *nuline, int *i)
{
	char	*expanval;
	char	tmpchr;
	int		tmppos;

	(*ogline)++;
	tmppos = get_varlen(*ogline);
	if (!tmppos)
	{
		nuline[(*i)++] = '$';
		return ;
	}
	tmpchr = ogline[0][tmppos];
	ogline[0][tmppos] = 0;
	expanval = ms_getenv(*ogline);
	*ogline = &ogline[0][tmppos];
	**ogline = tmpchr;
	tmppos = ft_strlen(expanval);
	ft_strlcpy(&nuline[*i], expanval, tmppos + 1);
	*i += tmppos;
}

static void	doublequotecpy(const char **ogline, char *nuline, int *i)
{
	(*ogline)++;
	while (**ogline != '\"')
	{
		if (**ogline == '$' && (ogline[0][1] && !ft_isspace(ogline[0][1])))
			dollarcpy((char **)ogline, nuline, i);
		else
			nuline[(*i)++] = *(*ogline)++;
	}
	(*ogline)++;
}

static void	singlequotecpy(const char **ogline, char *nuline, int *i)
{
	(*ogline)++;
	while (**ogline != '\'')
		nuline[(*i)++] = *(*ogline)++;
	(*ogline)++;
}

void	tokencpy(const char *ogline, int tknlen, char *nuline)
{
	int	i;

	i = 0;
	while (i < tknlen)
	{
		if (*ogline == '\'' && handle_quotes(ogline, *ogline))
			singlequotecpy(&ogline, nuline, &i);
		else if (*ogline == '\"' && handle_quotes(ogline, *ogline))
			doublequotecpy(&ogline, nuline, &i);
		else if (*ogline == '$')
			dollarcpy((char **)&ogline, nuline, &i);
		else
			nuline[i++] = *ogline++;
	}
}
