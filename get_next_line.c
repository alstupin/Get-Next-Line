/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alstupin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 15:13:32 by alstupin          #+#    #+#             */
/*   Updated: 2018/12/13 15:13:37 by alstupin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int	get_line(char **reste, char **line)
{
	char *tmp;

	if (!**reste)
	{
		//printf("end\n");
		return (0);
	}
	tmp = ft_strchr(*reste, '\n');
	if (tmp)
		*tmp = '\0';
	if (!(*line = ft_strdup(*reste)))
		return (-1);
	if (tmp)
	{
		if (!(*reste = ft_strdup(tmp + 1)))
			return (-1);		
	}
	else
	{
		ft_strdel(reste);
		//printf("CLEAN RESTE %s\n", *reste);
	}
	//printf("Reste end: %s\n", *reste);
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	char		*buf;
	static char	*reste;
	int rd;

	rd = 1;
	buf = ft_strnew(BUFF_SIZE);
	//printf("REste a l4entreé: %s\n", reste);
	while (rd > 0 && (!reste || (reste && !(ft_strchr(reste, '\n')))))
	{
		rd = read(fd, buf, BUFF_SIZE);
		if (rd == -1)
			return (-1);
		if (!reste)
		{
			if (!(reste = ft_strdup(buf)))
				return (-1);
		}
		else
			reste = ft_strjoin(reste, buf);
		ft_strclr(buf);
	}
	//printf("Buffer exit: %s\n", reste);
	return (get_line(&reste, line));
}

int     main(int c, char **v)
{
	char    *line;
	int     fd;
	int     i;
	int     out;

	if (c >= 2)
	{
		i = 0;
		if (!(fd = open(v[1], O_RDONLY)))
			return (0);
		line = NULL;
		out = get_next_line(fd, &line);
		while (out > 0)
		{
			i++;
			printf ("%d \t: %s\n", i, line);
			out = get_next_line(fd, &line);
			//printf("OUT ::::::::::::::::::::::::::::::::::::::::: %d\n", out);
		}
		free(line);
	}
	return (0);
}