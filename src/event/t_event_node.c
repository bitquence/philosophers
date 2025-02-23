#include "./t_event_node.h"

#include <stdlib.h>

t_event_node *evl_new(t_event event)
{
	t_event_node *node;

	node = malloc(sizeof(t_event_node));
	if (!node)
		return (NULL);
	*node = (t_event_node) {
		.next = NULL,
		.event = event,
	};
	return (node);
}

t_event_node *evl_pop_link_front(t_event_node **lst)
{
	t_event_node *backup;

	if (*lst == NULL)
		return (NULL);
	backup = (*lst);
	*lst = (*lst)->next;
	backup->next = NULL;
	return (backup);
}

void	evl_push_link_back(t_event_node **tail, t_event_node *link)
{
	if (!link)
		return;
	while ((*tail) && (*tail)->next)
		(*tail) = (*tail)->next;
	if (!*tail)
		*tail = link;
	else
	{
		( *tail )->next = link;
		*tail = link;
	}
}

void	evl_clear(t_event_node **lst)
{
	t_event_node *node;

	node = evl_pop_link_front(lst);
	while (node)
	{
		free(node);
		node = evl_pop_link_front(lst);
	}
}
