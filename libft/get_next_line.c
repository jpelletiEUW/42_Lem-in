/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelleti <jpelleti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 14:51:23 by gjuste            #+#    #+#             */
/*   Updated: 2019/10/25 16:29:33 by jpelleti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		empty_buffer(char **save)
{
	if (!**save)
	{
		free(*save);
		*save = NULL;
		save = NULL;
	}
	return (0);
}

static int		readline(int fd, char **str)
{
	int		error;
	char	buff[BUFF_SIZE + 1];
	char	*tmp;

	ft_bzero(buff, BUFF_SIZE + 1);
	while ((error = read(fd, buff, BUFF_SIZE)) > 0)
	{
		tmp = *str;
		if ((*str = ft_strjoin(*str, buff)) == NULL)
			return (-1);
		free(tmp);
		ft_bzero(buff, BUFF_SIZE + 1);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	return (error);
}

static char		*gnl_to_line(char **str)
{
	int				i;
	char			*ret;
	char			*tmp;

	i = 0;
	while (*(*str + i) != '\n' && *(*str + i) != '\0')
		i++;
	if ((ret = ft_strsub(*str, 0, i)) == NULL)
		return (NULL);
	tmp = *str;
	if ((*str = ft_strsub(*str, i + 1, ft_strlen(*str) - i)) == NULL)
		return (NULL);
	free(tmp);
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str;
	int				error;

	if (fd < 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!str)
		if (!(str = ft_strnew(0)))
			return (-1);
	if (ft_strchr(str, '\n') != NULL)
	{
		if ((*line = gnl_to_line(&str)) == NULL)
			return (-1);
	}
	else
	{
		if ((error = readline(fd, &str)) == 0 && !*str)
			return (empty_buffer(&str));
		if (error == -1)
			return (-1);
		if ((*line = gnl_to_line(&str)) == NULL)
			return (-1);
	}
	return (1);
}
