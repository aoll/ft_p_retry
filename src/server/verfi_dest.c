/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verfi_dest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 00:06:02 by alex              #+#    #+#             */
/*   Updated: 2018/06/21 01:12:11 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

static char	*cmp_pwd_dest(t_cs *cs, char *dest)
{
	char *tmp;

	if (dest[0] == '/')
	{
		tmp = ft_strjoin(cs->home, dest);
	}
	else
	{
		tmp = ft_strjoin(cs->pwd, "/");
		tmp = ft_strjoin_free(&tmp, dest);
	}
	return (tmp);
}

static int	verify_dest_chidr(t_cs *cs, char *dest)
{
	char	*s;
	int		cmp;
	char	*tmp;

	tmp = cmp_pwd_dest(cs, dest);
	if (chdir(tmp))
	{
		free(tmp);
		return (EXIT_FAILLURE);
	}
	free(tmp);
	if (!(s = ft_strnew(PWD_MAX_LEN)))
		return (EXIT_FAILLURE);
	if (!(s = getcwd(s, PWD_MAX_LEN)))
		return (EXIT_FAILLURE);
	cmp = ft_strncmp(s, cs->home, ft_strlen(cs->home));
	free(s);
	if (chdir(cs->pwd))
		return (EXIT_FAILLURE);
	return (cmp);
}

int			verify_dest_get(t_cs *cs, char *dest)
{
	int		i;
	char	*tmp;
	int		ret;
	int		len;

	len = ft_strlen(dest);
	i = len - 1;
	while (i && dest[i] != '/')
		i--;
	if (i)
		tmp = ft_strsub(dest, 0, i);
	else
		tmp = ft_strdup("");
	ret = verify_dest_chidr(cs, tmp);
	free(tmp);
	return (ret);
}

int			verify_dest(t_cs *cs, char *dest)
{
	if (verify_dest_chidr(cs, dest))
		return (EXIT_FAILLURE);
	return (EXIT_SUCCESS);
}

int			verify_multi_dest(t_cs *cs, char **requet)
{
	int i;

	i = 0;
	if (!*requet)
		return (EXIT_SUCCESS);
	while (requet[i] && *requet[i] == '-')
		i++;
	while (requet[i])
	{
		if (verify_dest(cs, requet[i]))
			return (EXIT_FAILLURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
