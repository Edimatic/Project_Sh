#include "function.h"

/**
 * add_node - Adds a new node to the start of a linked list.
 *
 * @boss: Address of the pointer to the head node.
 * @strn: String field of the new node.
 * @noms: Node index used by history
 *
 * Return: Pointer to the new head of the list after execution.
 */
list_t *add_node(list_t **boss, const char *strn, int noms)
{
	list_t *new_boss;

	if (!boss)
		return (NULL);

	/* Allocate memory for the new node */
	new_boss = malloc(sizeof(list_t));
	if (!new_boss)
		return (NULL);

	/* Initialize the new node */
	_memset((void *)new_boss, 0, sizeof(list_t));
	new_boss->num = noms;
	if (strn)
	{
		new_boss->str = _strdup_(strn);
		if (!new_boss->str)
		{
			free(new_boss);
			return (NULL);
		}
	}

	/* Update the new node's 'next' pointer and the list's head */
	new_boss->next = *boss;
	*boss = new_boss;
	return (new_boss);
}

/**
 * add_node_end - Adds a new node to the end of a linked list.
 *
 * @boss: Address of the pointer to the head node.
 * @strn: String field of the new node.
 * @noms: Node index used by history.
 *
 * Return: Pointer to the new node added to the end.
 */
list_t *add_node_end(list_t **boss, const char *strn, int noms)
{
	list_t *new_node, *node;

	if (!boss)
		return (NULL);

	/* Create a new node and initialize it */
	node = *boss;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = noms;
	if (strn)
	{
		new_node->str = _strdup_(strn);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

/* If the list is not empty, find the last node and append the new node */
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*boss = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 *
 * @hd: Pointer to the first node of the list.
 *
 * Return: Size of the list
 */
size_t print_list_str(const list_t *hd)
{
	size_t w = 0;

	while (hd)
	{
		/* Print the 'str' element or "(nil)" */
		_puts_(hd->str ? hd->str : "(nil)");
		_puts_("\n");
		hd = hd->next;
		w++;
	}
	return (w);
}

/**
 * delete_node_at_index - Deletes a node at a given index from a linked list.
 *
 * @boss: Address of pointer to the first node
 * @sufix: Index of the node to deleted.
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **boss, unsigned int sufix)
{
	list_t *node, *prev_node;
	unsigned int y = 0;

	if (!boss || !*boss)
		return (0);

	if (!sufix)/* If index is 0, remove the first node */
	{
		node = *boss;
		*boss = (*boss)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *boss;
	while (node)
	{
		if (y == sufix)/* Found the node to delete */
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		y++;
		prev_node = node;
		node = node->next;
	}
	return (0);/* Node at the given index was not found */
}

/**
 * free_list - Frees all nodes of a list.
 *
 * @boss_pt: Address of the  pointer to the head node.
 *
 * Return: void after execution.
 */
void free_list(list_t **boss_pt)
{
	list_t *node, *next_node, *boss;

	if (!boss_pt || !*boss_pt)
		return;
	boss = *boss_pt;
	node = boss;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*boss_pt = NULL;
}

