/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:21:26 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 10:21:33 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int index)
{
	if ('0' <= index && index <= '9')
		return (1);
	return (0);
}

static int	is_space(char c)
{
	char	*str;

	str = "\t\n\v\f\r ";
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	ans;
	int	result;

	if (!str)
		return (-1);
	ans = 0;
	result = 1;
	while (is_space(*str))
		str++;
	if (*str == '-')
		return (-1);
	if (*str == '+' || *str == '-')
		return (-1);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		ans = (ans * 10) + (*str - '0');
		str++;
	}
	return (result * ans);
}

int	find_map(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '0' || map[i] == '1')
			return (1);
		i++;
	}
	return (0);
}
