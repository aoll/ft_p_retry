/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 13:31:40 by aollivie          #+#    #+#             */
/*   Updated: 2018/06/21 01:09:51 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int	dup_std(int fd1_dst, int fd1_src, int fd2_dst, int fd2_src)
{
	if (dup2(fd1_dst, fd1_src) == -1 || dup2(fd2_dst, fd2_src) == -1)
		return (EXIT_FAILLURE);
	return (EXIT_SUCCESS);
}

static char	**ft_concat_path(char **arg, t_cs *cs)
{
	int		i;
	char	*tmp;

	i = 0;
	while (arg[i])
	{
		if (*arg[i] == '-')
		{
			i++;
			continue ;
		}
		else if (*arg[i] == '/')
			tmp = ft_strjoin(cs->home, arg[i]);
		else
		{
			tmp = ft_strjoin(cs->home, "/");
			tmp = ft_strjoin_free(&tmp, arg[i]);
		}
		free(arg[i]);
		arg[i] = tmp;
		i++;
	}
	return (arg);
}

int			fork_process_cmd(int fd, char **arg, t_cs *cs)
{
	pid_t	pid;
	int		ret;
	int		status;

	if ((pid = fork()) == -1)
		return (-1);
	if (!pid)
	{
		if (dup_std(fd, STDOUT, fd, STDERR))
			return (send_error(fd, INTERN_ERROR));
		execv("/bin/ls", ft_concat_path(arg, cs));
		exit(-1);
	}
	else
	{
		wait4(pid, &status, 0, NULL);
		ret = WEXITSTATUS(status);
		return (ret);
	}
	return (EXIT_SUCCESS);
}
