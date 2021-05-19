/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wquenten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 21:00:17 by wquenten          #+#    #+#             */
/*   Updated: 2021/05/09 20:14:29 by masai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	while (len && ft_strchr(set, *s1) && s1++)
		len--;
	while (len && ft_strchr(set, s1[len - 1]))
		len--;
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = s1[i];
	new[i] = '\0';
	return (new);
}
