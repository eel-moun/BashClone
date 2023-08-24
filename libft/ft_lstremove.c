/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btaha <btaha@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:16:04 by btaha             #+#    #+#             */
/*   Updated: 2022/12/27 18:16:11 by btaha            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove(t_list **lst, t_list *to_rm)
{
	t_list	*pre;
	t_list	*cur;

	pre = NULL;
	cur = *lst;
	while (cur)
	{
		if (cur == to_rm)
		{
			if (pre)
				pre->next = cur->next;
			else
				*lst = cur->next;
			return ;
		}
		pre = cur;
		cur = cur->next;
	}
}
