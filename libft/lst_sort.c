/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 12:09:04 by btaha             #+#    #+#             */
/*   Updated: 2022/12/23 16:15:40 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_sort(t_list **lst, t_list *new, t_cmpfn cmpfn)
{
	t_list	*cur;
	t_list	*pre;

	cur = *lst;
	if (!cur || cmpfn(cur->content, new->content) > 0)
		ft_lstadd_front(lst, new);
	else
	{
		pre = cur;
		cur = cur->next;
		while (cur && cmpfn(cur->content, new->content) <= 0)
		{
			pre = cur;
			cur = cur->next;
		}
		new->next = cur;
		pre->next = new;
	}
}
