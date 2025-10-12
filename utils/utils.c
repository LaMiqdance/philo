/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midiagne <midiagne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:34:12 by midiagne          #+#    #+#             */
/*   Updated: 2025/10/12 19:37:12 by midiagne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char    *ft_strdup(char *s)
{
    char    *str;
    int     i;
    
    str = malloc(sizeof(char) * ft_strlen(s) + 1);
    if (!str)
        return (NULL);
    i = 0;
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i]  = '\0';
    return (str);
}
