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

void	evl_push_link_front(t_event_node **lst, t_event_node *link)
{
	if (!link)
		return;
	link->next = *lst;
	*lst = link;
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
