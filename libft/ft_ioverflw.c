/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioverflw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntamayo- <ntamayo-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 12:37:36 by ntamayo-          #+#    #+#             */
/*   Updated: 2022/08/10 16:01:24 by ntamayo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ioverflw(char *str)
{
	int	len;
	int	num;

	num = ft_atoi(str);
	len = ft_strlen(str);
	if (*str == '-')
		if (!num || len > 11 || (len == 11 && str[1] > '2'))
			return (1);
	if (*str != '-')
		if (num == -1 || len > 10 || (len == 10 && str[0] > '2'))
			return (1);
	return (0);
}
