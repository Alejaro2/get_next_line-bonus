/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejaro2 <alejaro2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:55:12 by alejaro2          #+#    #+#             */
/*   Updated: 2024/12/22 21:37:16 by alejaro2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*updated_accumulated(char *accumulated)
{
	char	*ptr;
	char	*temp;
	int		len;
	int		i;

	ptr = ft_strchr(accumulated, '\n');
	if (ptr != NULL)
		len = ft_strlen(ptr + 1);
	else
		return (NULL);
	if (len == 0)
		return (NULL);
	temp = malloc((len + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ptr++;
	i = 0;
	while (i < len)
	{
		temp[i] = ptr[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*extract_line(char *accumulated)
{
	char	*ptr;
	char	*line;
	size_t	len;

	if (!accumulated)
		return (NULL);
	ptr = ft_strchr(accumulated, '\n');
	if (ptr != NULL)
		len = (ptr - accumulated) + 1;
	else
		len = ft_strlen(accumulated);
	line = calloc((len + 1), sizeof(char));
	if (!line)
		return ((free(line)), NULL);
	ft_strlcpy(line, accumulated, len + 1);
	line[len] = 0;
	return (line);
}

char	*read_until(int fd, char *accumulated)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(accumulated), NULL);
	bytes = 1;
	while (ft_strchr(accumulated, '\n') == NULL && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return ((free(accumulated), free(buffer), NULL));
		if (bytes == 0)
			return (free(buffer), accumulated);
		buffer[bytes] = '\0';
		accumulated = ft_strjoin(accumulated, buffer);
		if (!accumulated)
			return (free(buffer), NULL);
	}
	return (free(buffer), accumulated);
}

char	*get_next_line(int fd)
{
	static char	*accumulated[1024];
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	accumulated[fd] = read_until(fd, accumulated[fd]);
	if (!accumulated[fd])
		return (NULL);
	line = extract_line(accumulated[fd]);
	temp = updated_accumulated(accumulated[fd]);
	free(accumulated[fd]);
	accumulated[fd] = temp;
	return (line);
}
/*int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("hola1.txt", O_RDONLY);
	fd2 = open("hola2.txt", O_RDONLY);
	while ((line = get_next_line(fd1)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("%c", '\n');
	while ((line = get_next_line(fd2)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd1);
	close(fd2);
	return (0);
}*/
