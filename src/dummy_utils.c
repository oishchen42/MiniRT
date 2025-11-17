#include <minirt.h>

void 	free_double(char **split)
{
	int i = -1;
	while (split[++i])
	{
		free(split[i]);
	}
	free(split);
}

void	pirnt_split_content(char **split)
{
	int i = -1;
	while (split[++i])
	{
		printf("%s\n", split[i]);
	}
}
