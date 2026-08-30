/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 17:14:21 by thacharo          #+#    #+#             */
/*   Updated: 2026/08/30 17:22:31 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_segments(char *s, char c);
static int	split_words(char **arr, char const *s, char c, int segments);
static char	**map_format_splitter(char *s, char c);
static char	*append_line(char *s1, char *s2);

char	**read_file(int fd)
{
	char	*line;
	char	*joined;
	char	**lines;

	line = NULL;
	joined = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!joined)
			joined = line;
		else
		{
			joined = append_line(joined, line);
			if (!joined)
				return (NULL);
		}
	}
	lines = map_format_splitter(joined, '\n');
	free(joined);
	return (lines);
}

static char	*append_line(char *s1, char *s2)
{
	char	*buffer;
	char	*joined;

	buffer = s1;
	joined = ft_strjoin(buffer, s2);
	free(buffer);
	free(s2);
	return (joined);
}

static int	split_words(char **arr, char const *s, char c, int segments)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			arr[j] = ft_substr(s, start, i - start);
			if (!arr[j++])
				return (free_arr(arr, j - 1));
			start = i + 1;
		}
		i++;
	}
	if (j >= (size_t)segments)
		return (1);
	arr[j] = ft_substr(s, start, i - start);
	if (!arr[j])
		return (free_arr(arr, j));
	return (1);
}

static char	**map_format_splitter(char *s, char c)
{
	int		segments;
	char	**words;

	words = NULL;
	if (s == NULL)
		return (NULL);
	segments = count_segments(s, c);
	words = (char **)malloc(sizeof(char *) * (segments + 1));
	if (!words)
		return (NULL);
	if (!split_words(words, s, c, segments))
		return (NULL);
	words[segments] = NULL;
	return (words);
}

static int	count_segments(char *s, char c)
{
	int	i;
	int	n;

	n = 1;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			n++;
		i++;
	}
	if (i > 0 && s[i - 1] == c)
		n--;
	return (n);
}
