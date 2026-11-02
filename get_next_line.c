#include "get_next_line.h"

static char	*ft_strchr(const char *s, int c)
{
	int				count;
	unsigned char	ch;

	count = 0;
	ch = c;
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	count = 0;
	while (s[count])
	{
		if (s[count] == ch)
			return ((char *)&s[count]);
		count++;
	}
	return (NULL);
}

static int	read_to_temp(int fd, char **temp)
{
	char	*buffer;
	char	*old;
	int		byte;

	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (0);
	byte = read(fd, buffer, BUFFER_SIZE);
	while (byte > 0)
	{
		buffer[byte] = '\0';
		old = *temp;
		*temp = ft_strjoin(old, buffer);
		free(old);
		if (*temp == NULL || ft_strchr(*temp, '\n') != NULL)
			break ;
		byte = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (byte == -1)
	{
		free(*temp);
		*temp = NULL;
	}
	return (1);
}

static char	*extract_line(char **temp)
{
	char	*str;
	char	*old;
	int		i;

	i = 0;
	while ((*temp)[i] && (*temp)[i] != '\n')
		i++;
	i += ((*temp)[i] == '\n');
	str = ft_substr(*temp, 0, i);
	old = *temp;
	*temp = NULL;
	if (str != NULL)
		*temp = ft_substr(old, i, ft_strlen(old) - i);
	free(old);
	if (str == NULL || *temp == NULL)
	{
		free(str);
		return (NULL);
	}
	if ((*temp)[0] == '\0')
	{
		free(*temp);
		*temp = NULL;
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*temp;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (read_to_temp(fd, &temp) == 0)
		return (NULL);
	if (temp == NULL || temp[0] == '\0')
		return (NULL);
	return (extract_line(&temp));
}
