/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:38:53 by ailbezer          #+#    #+#             */
/*   Updated: 2024/11/15 14:39:03 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_free_line(t_list *list)
{
	t_nod	*temp;
	t_nod	*new_node;
	char	*leftover;
	int		i;
	int		size;

	if (!list || !list->head)
		return ;
	temp = list->tail;
	leftover = temp->content;
	size = temp->length;
	temp->content = NULL;
	ft_lstclear(list);
	i = 0;
	if (leftover[size] != '\0')
	{
		while (leftover[size] != '\0')
			leftover[i++] = leftover[size++];
		leftover[i] = '\0';
		new_node = ft_new_node(leftover);
		ft_append(list, new_node);
	}
	else
		free(leftover);
	list->tail = list->head;
}

static void	ft_build_line(t_list *list, char **line)
{
	t_nod	*temp;
	int		line_size;
	int		i;

	temp = list->head;
	line_size = 0;
	while (temp)
	{
		line_size += temp->length;
		temp = temp->next;
	}
	*line = malloc(line_size + 1);
	if (!*line)
		return ;
	line_size = 0;
	temp = list->head;
	while (temp && temp->content)
	{
		i = 0;
		while (temp->content[i] && i < temp->length)
			(*line)[line_size++] = temp->content[i++];
		temp = temp->next;
	}
	(*line)[line_size] = '\0';
}

static int	ft_check_newline(t_list *list)
{
	int	i;

	if (!list->head || !list->tail)
		return (0);
	i = 0;
	while (list->tail->content[i] != '\0')
	{
		if (list->tail->content[i] == '\n')
		{
			list->line_size += ++i;
			list->tail->length = i;
			return (1);
		}
		i++;
	}
	list->line_size += i;
	list->tail->length = i;
	return (0);
}

static void	ft_save_data(t_list *list, int fd)
{
	int		chars;
	t_nod	*new_node;

	while (!ft_check_newline(list))
	{
		new_node = ft_new_node(NULL);
		new_node->content = malloc(BUFFER_SIZE + 1);
		if (!new_node->content)
			return ;
		chars = read(fd, new_node->content, BUFFER_SIZE);
		if (chars <= 0)
		{
			free(new_node->content);
			free(new_node);
			if (chars == -1)
				ft_lstclear(list);
			return ;
		}
		new_node->content[chars] = '\0';
		ft_append(list, new_node);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list[OPEN_MAX] = {NULL};
	char			*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if (!list[fd])
		list[fd] = ft_new_list();
	ft_save_data(list[fd], fd);
	if (!list[fd] || !list[fd]->head)
	{
		free(list[fd]);
		list[fd] = NULL;
		return (NULL);
	}
	ft_build_line(list[fd], &line);
	ft_free_line(list[fd]);
	return (line);
}
