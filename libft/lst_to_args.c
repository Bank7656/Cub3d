/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_to_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thacharo <thacharo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:18:37 by thacharo          #+#    #+#             */
/*   Updated: 2026/04/16 13:38:51 by thacharo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clear_array(char **arr, int i);

char	**lst_to_args(t_list *lst)
{
	int		i;
	int		size;
	char	**args;
	t_list	*tmp;

	size = ft_lstsize(lst);
	args = (char **)malloc(sizeof(char *) * (size + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		args[i] = ft_strdup((char *)tmp->content);
		if (args[i] == NULL)
		{
			clear_array(args, i);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

static void	clear_array(char **arr, int i)
{
	while (i <= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return ;
}
