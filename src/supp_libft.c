/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:12:16 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:13:39 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

double	ft_atod(char *str)
{
	t_atod	nb;

	nb.res = 0.0;
	nb.factor = 1.0;
	nb.sign = 1;
	nb.i = 0;
	if (str[nb.i] == '-')
	{
		nb.sign = -1;
		nb.i++;
	}
	while (str[nb.i] && ft_isdigit(str[nb.i]))
		nb.res = nb.res * 10.0 + (str[nb.i++] - '0');
	if (str[nb.i] == '.')
		nb.i++;
	while (str[nb.i] && ft_isdigit(str[nb.i]))
	{
		nb.factor /= 10.0;
		nb.res += (str[nb.i++] - '0') * nb.factor;
	}
	return (nb.res * nb.sign);
}

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (!split)
		return ;
	while (split[++i])
	{
		free(split[i]);
		split[i] = NULL;
	}
	free(split);
	split = NULL;
}

int	valid_str(char *str)
{
	int		j;
	int		n_dot;
	size_t	str_len;

	n_dot = 0;
	j = -1;
	str_len = ft_strlen(str);
	if (str[++j] == '-')
		j++;
	while (str[++j] && n_dot < 2)
	{
		if (str[j] == '.')
		{
			n_dot++;
			if (n_dot > 1)
				return (0);
		}
		else if (!ft_isdigit(str[j]))
			return (0);
	}
	return (1);
}

int	check_tokens(char **split)
{
	int	sp_count;
	int	j;

	sp_count = -1;
	while (split[++sp_count])
		;
	j = -1;
	while (++j < sp_count && valid_str(split[j]))
		;
	if (j != sp_count)
		return (0);
	return (1);
}

int	get_vector(char *str, t_vcpnt *vec, double is_pnt)
{
	char	**tokens;

	tokens = ft_split(str, ',');
	if (!tokens || !tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
		return (free_split(tokens), 0);
	if (!check_tokens(tokens))
		return (free_split(tokens), 0);
	vec->vp[0] = ft_atod(tokens[0]);
	vec->vp[1] = ft_atod(tokens[1]);
	vec->vp[2] = ft_atod(tokens[2]);
	vec->vp[3] = is_pnt;
	free_split(tokens);
	return (1);
}
