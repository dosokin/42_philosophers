/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dosokin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:21:32 by dosokin           #+#    #+#             */
/*   Updated: 2024/10/18 20:26:16 by dosokin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

t_lst_philo *lst_philo_get_last(t_lst_philo *head)
{
    if (!head)
        return (NULL);
    while (head->next)
        head = head->next;
    return (head);
}

size_t	ft_lst_size(t_lst_philo *head)
{
	size_t	elements_count;
	t_lst_philo	*tempo;

	if (!head)
		return (0);
	elements_count = 0;
	tempo = head;
	while (tempo->next != head)
	{
		elements_count++;
		tempo = tempo->next;
	}
	elements_count++;
	return (elements_count);
}

void	ft_lst_philo_clear(t_lst_philo *head)
{
	t_lst_philo	*current;
	t_lst_philo	*next;

	if (!head)
		return ;
	current = head;
	while (current->next != head)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
}

void	ft_lst_philo_addback(t_lst_philo **head, t_lst_philo *new)
{
	t_lst_philo	*tempo;

	if (!head || !new)
		return ;
	tempo = *head;
	if (!tempo)
	{
		*head = new;
		return ;
	}
    lst_philo_get_last(*head)->next = new;
	new->next = NULL;
}
//
//t_lst_philo	*ft_lst_philo_new(t_lst_philo *head)
//{
//	head->next = head;
//	head->prev = head;
//	return (head);
//}
