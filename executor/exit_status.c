/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phijano- <phijano-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:50:29 by phijano-          #+#    #+#             */
/*   Updated: 2022/09/13 11:18:01 by phijano-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_exit_status(int status)
{
	int	exit;

	exit = 0;
	if (((status) & 0x7f) == 0)
		exit = 1;
	return (exit);
}

int	ft_exit_code(int status)
{
	return (((status) & 0xff00) >> 8);
}
