/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kenguyen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 18:40:31 by kenguyen          #+#    #+#             */
/*   Updated: 2017/11/14 15:35:04 by kenguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;

	s = s1;
	while (*s)
		s++;
	while (*s2 && n-- > 0)
		*s++ = *s2++;
	*s = '\0';
	return (s1);
}
