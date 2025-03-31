/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ailbezer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:40:21 by ailbezer          #+#    #+#             */
/*   Updated: 2024/11/15 14:40:28 by ailbezer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_node
{
	char			*content;
	int				length;
	struct s_node	*next;
}					t_nod;

typedef struct s_list
{
	t_nod	*head;
	int		line_size;
	t_nod	*tail;
}			t_list;

char	*get_next_line(int fd);
t_list	*ft_new_list(void);
t_nod	*ft_new_node(char *content);
void	ft_lstclear(t_list *list);
void	ft_append(t_list *list, t_nod *new_node);

#endif
