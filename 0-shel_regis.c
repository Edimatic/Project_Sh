#include "function.h"

/**
 * attach_node - Adds a new node to the start of a linked list.
 *
 * @boss: Address of the pointer to the head node.
 * @strn: String field of the new node.
 * @noms: Node index used by history
 *
 * Return: Pointer to the new head of the list after execution.
 */
regis_t *attach_node(regis_t **boss, const char *strn, int noms)
{
	regis_t *new_boss;

	if (!boss)
		return (NULL);

	/* Allocate memory for the new node */
	new_boss = malloc(sizeof(regis_t));
	if (!new_boss)
		return (NULL);

	/* Initialize the new node */
	_wmanpro((void *)new_boss, 0, sizeof(regis_t));
	new_boss->figure = noms;
	if (strn)
	{
		new_boss->rop = _strdup_(strn);
		if (!new_boss->rop)
		{
			free(new_boss);
			return (NULL);
		}
	}

	/* Update the new node's 'next' pointer and the list's head */
	new_boss->after = *boss;
	*boss = new_boss;
	return (new_boss);
}

/**
 * attach_node_end - Adds a new node to the end of a linked list.
 *
 * @boss: Address of the pointer to the head node.
 * @strn: String field of the new node.
 * @noms: Node index used by history.
 *
 * Return: Pointer to the new node added to the end.
 */
regis_t *attach_node_end(regis_t **boss, const char *strn, int noms)
{
	regis_t *new_node, *node;

	if (!boss)
		return (NULL);

	/* Create a new node and initialize it */
	node = *boss;
	new_node = malloc(sizeof(regis_t));
	if (!new_node)
		return (NULL);
	_wmanpro((void *)new_node, 0, sizeof(regis_t));
	new_node->figure = noms;
	if (strn)
	{
		new_node->rop = _strdup_(strn);
		if (!new_node->rop)
		{
			free(new_node);
			return (NULL);
		}
	}

/* If the list is not empty, find the last node and append the new node */
	if (node)
	{
		while (node->after)
			node = node->after;
		node->after = new_node;
	}
	else
		*boss = new_node;
	return (new_node);
}

/**
 * output_reg_strn - prints only the str element of a list_t linked list
 *
 * @hd: Pointer to the first node of the list.
 *
 * Return: Size of the list
 */
size_t output_reg_strn(const regis_t *hd)
{
	size_t w = 0;

	while (hd)
	{
		/* Print the 'str' element or "(nil)" */
		_puts_(hd->rop ? hd->rop : "(nil)");
		_puts_("\n");
		hd = hd->after;
		w++;
	}
	return (w);
}

/**
 * remov_node_via_roll - Deletes a node at a given index from a linked list.
 *
 * @boss: Address of pointer to the first node
 * @sufix: Index of the node to deleted.
 *
 * Return: 1 on success, 0 on failure
 */
int remov_node_via_roll(regis_t **boss, unsigned int sufix)
{
	regis_t *node, *prev_node;
	unsigned int y = 0;

	if (!boss || !*boss)
		return (0);

	if (!sufix)/* If index is 0, remove the first node */
	{
		node = *boss;
		*boss = (*boss)->after;
		free(node->rop);
		free(node);
		return (1);
	}
	node = *boss;
	while (node)
	{
		if (y == sufix)/* Found the node to delete */
		{
			prev_node->after = node->after;
			free(node->rop);
			free(node);
			return (1);
		}
		y++;
		prev_node = node;
		node = node->after;
	}
	return (0);/* Node at the given index was not found */
}

/**
 * empty_register - Frees all nodes of a list.
 *
 * @boss_pt: Address of the  pointer to the head node.
 *
 * Return: void after execution.
 */
void empty_register(regis_t **boss_pt)
{
	regis_t *node, *next_node, *boss;

	if (!boss_pt || !*boss_pt)
		return;
	boss = *boss_pt;
	node = boss;
	while (node)
	{
		next_node = node->after;
		free(node->rop);
		free(node);
		node = next_node;
	}
	*boss_pt = NULL;
}

