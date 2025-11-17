/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:05:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/16 16:40:06 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_split_value(char **value)
{
	int	val_counter;
	if (!value)
		return(perror("NO VALUE check_split_value"), 0);
	val_counter = -1;
	while (value[++val_counter])
		;
	if (ft_strncmp(value[0], "A", ft_strlen("A")) != 0 && val_counter + 1 != 3)
	{
		return (perror("Wrong value || Wrong value nb"), 0);
	}
	return (1);
}

int	is_rt(char *str)
{
	int		i;
	char	*ext;

	i = -1;
	ext = ft_strchr(str, '.');
	printf("%s\n", ext);
	if (ft_strncmp(ext, ".rt", ft_strlen(ext) + 1) != 0)
	{
		perror("Wrong file extension");
		return (0);
	}
	printf("Valid input\n"); // delete
	return (1);
}

t_test *get_value(char *file) // norm
{
	int		fd;
	char	*content;
	char	**split_content;

	// printf("%s\n", file);
	fd = open(file, O_RDONLY);
	// printf("%d\n", fd);

	if (fd < 0)
	{
		printf("%d\n", fd);
		perror("file not found");
		return (NULL);
	}

	content = get_next_line(fd);
	if (!content)
		perror("SMTH IS WRONG gnl"); //delete
	else
		printf("%s", content);
	split_content = ft_split(content, '\t');
	if (!split_content)
		perror("SMTH IS WRONG split");
	check_split_value(split_content);
	pirnt_split_content(split_content);
	free_double(split_content);
	free(content);
	return (NULL);
}
