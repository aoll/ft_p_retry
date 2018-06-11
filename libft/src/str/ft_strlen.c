/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:51:56 by aollivie          #+#    #+#             */
/*   Updated: 2015/03/01 16:19:47 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	if (s)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		return (i);
	}
	return (0);
}
