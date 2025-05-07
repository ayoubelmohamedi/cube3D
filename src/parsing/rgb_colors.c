/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:15:07 by aez-zoui          #+#    #+#             */
/*   Updated: 2025/05/07 10:15:09 by aez-zoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//   result = (R≪16)+ (G≪8)+ B 
//   https://chatgpt.com/share/681b3dd8-e11c-8008-bff1-faeaf9f9da9a
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
