/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-moha <ael-moha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:33:22 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/05 21:19:47 by ael-moha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	rgb_to_int(int red, int green, int blue)
{
	int	shifted_red;
	int	shifted_green;
	int	shifted_blue;
	int	result;

	shifted_red = red << 16;
	shifted_green = green << 8;
	shifted_blue = blue;
	result = shifted_red | shifted_green | shifted_blue;
	return (result);
}

int	get_colors(char *rgb)
{
	char	**colors;
	int		red;
	int		green;
	int		blue;
	int		result;

	colors = ft_split(rgb, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		free_array(colors);
		return (-1);
	}
	red = ft_atoi(colors[0]);
	green = ft_atoi(colors[1]);
	blue = ft_atoi(colors[2]);
	free_array(colors);
	result = rgb_to_int(red, green, blue);
	return (result);
}
