/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:51:25 by ailbezer          #+#    #+#             */
/*   Updated: 2024/11/15 17:51:34 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_nod	*ft_new_node(char *content)
{
	t_nod		*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->length = 0;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstclear(t_list *list)
{
	t_nod	*temp;

	if (!list || !list->head)
		return ;
	while (list->head != NULL)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp->content);
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}

t_list	*ft_new_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->line_size = 0;
	list->tail = NULL;
	return (list);
}

void	ft_append(t_list *list, t_nod *new_node)
{
	if (!list || !new_node)
		return ;
	if (list->head == NULL)
	{
		list->head = new_node;
		list->tail = new_node;
	}
	else
	{
		list->tail->next = new_node;
		list->tail = new_node;
	}
}
