/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:34:15 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/09/27 13:41:24 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msparser.h"

static int	expand_this(char **this)
{
	int		i;
	int		tokenlen;
	char	*temp;

	i = 0;
	while (this[i])
	{
		if (need_expansion(this[i]))
		{
			tokenlen = get_tknlen(this[i]);
			temp = ft_calloc(tokenlen + 1, sizeof(char));
			if (!temp)
				return (1);
			tokencpy(this[i], tokenlen, temp);
			free(this[i]);
			this[i] = temp;
		}
		i++;
	}
	return (0);
}

int	expand_quotes(t_parsing *cts)
{
	while (!cts->islast)
	{
		expand_this(cts[0].cmndtable);
		expand_this(cts[0].ins);
		expand_this(cts[0].outs);
		cts++;
	}
	return (0);
}
