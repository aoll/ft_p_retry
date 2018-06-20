/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 00:31:05 by alex              #+#    #+#             */
/*   Updated: 2018/06/20 22:11:07 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	exec_cmd(int fd, char **requet, t_cs *cs)
{
	int		ret;
	char	*end;

	if (!(end = ft_strnew(1)))
		return (send_error(fd, INTERN_ERROR));
	ft_bzero(end, 1);
	ret = fork_process_cmd(fd, requet, cs);
	end[0] = EOT;
	ret = send(fd, end, 1, 0);
	free(end);
	if ((ret = wait_reponse(fd, R_SUCCESS, -1, NO_LOG)))
		return (ret);
	return (ret < 0 ? send_error(fd, INTERN_ERROR) : send_success(fd));
}

int			cmd_requet(t_cs *cs, char **requet)
{
	int	ret;

	if (verify_multi_dest(cs, requet + 1))
		return (send_error(cs->fd, NO_ACCESS));
	if ((ret = send_requet(
		cs->fd, R_CMD_OK, 0, NULL)))
		return (ret);
	if (wait_reponse(cs->fd, R_WAIT_RECV, -1, NO_LOG) < 0)
		return (send_error(cs->fd, INTERN_ERROR));
	ret = exec_cmd(cs->fd, requet, cs);
	return (ret);
}
