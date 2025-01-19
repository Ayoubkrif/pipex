/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayoub <ayoub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 18:02:30 by ayoub             #+#    #+#             */
/*   Updated: 2024/11/13 09:06:52 by aykrifa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isisspace(int c)
{
	return ((c <= 13 && c >= 9) || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	r;
	int	s;

	s = 1;
	r = 0;
	while (ft_isisspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			s = -s;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		r = r * 10 + *nptr - '0';
		nptr++;
	}
	return (s * r);
}
