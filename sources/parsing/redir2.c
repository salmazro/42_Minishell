/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: salmazro <salmazro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:26:28 by salmazro          #+#    #+#             */
/*   Updated: 2022/12/19 17:58:47 by salmazro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	checkheredoc_status(int stat, int fd)
{
	if (WEXITSTATUS(stat))
	{
		g_appinfo.exit_status = WEXITSTATUS(stat);
		close(fd);
		g_appinfo.pipe_out = -1;
	}
}
