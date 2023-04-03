/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:49:40 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/27 13:23:48 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

int	need_expansion(const char *str)
{
	int	temp;
	int	expandflag;

	expandflag = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			temp = handle_quotes(str, *str);
			if (temp)
				expandflag = 1;
			str += temp;
		}
		else if (*str == '$' && !ft_isspace(str[1]) && str[1])
			expandflag = 1;
		str++;
	}
	return (expandflag);
}

int	get_varlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != '\''
		&& str[i] != '\"' && !ft_isspace(str[i]))
		i++;
	return (i);
}

static int	expand_dollar(const char *str, int *i)
{
	int		ret;
	char	*var;

	if (!str[1])
		return (1);
	ret = get_varlen(&str[*i + 1]);
	var = ft_substr(&str[*i], 1, ret);
	*i += ret;
	ret = ft_strlen(ms_getenv(var));
	free(var);
	if (ret > -1)
		return (ret);
	return (0);
}

static int	get_quotelen(const char *str, const char flag, int *i)
{
	int	qlen;

	qlen = 0;
	(*i)++;
	while (str[*i] && str[*i] != flag)
	{
		if (str[*i] == '$' && flag == '\"')
			qlen += expand_dollar(str, i);
		else
			qlen++;
		(*i)++;
	}
	return (qlen);
}

int	get_tknlen(const char *str)
{
	int	tlen;
	int	i;

	i = 0;
	tlen = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"')
			&& handle_quotes(&str[i], str[i]))
			tlen += get_quotelen(str, str[i], &i);
		else if (str[i] == '$')
			tlen += expand_dollar(str, &i);
		else
			tlen++;
		i++;
	}
	return (tlen);
}
