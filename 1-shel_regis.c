#include "function.h"

/**
 * register_extent - Determines length of linked list over
 *
 * @md: Pointer to first the node
 *
 * Return: Size of the list after execution
 */
size_t register_extent(const regis_t *md)
{
	size_t lp = 0;

	while (md)
	{
		md = md->after;
		lp++;
	}
	return (lp);
}

/**
 * register_via_strn - Converts a linked list of strns into an array of strns
 *
 * @boss: Pointer to the first node
 *
 * Return: Array of strings after execution
 */
char **register_via_strn(regis_t *boss)
{
	regis_t *node = boss;
	size_t q = register_extent(boss), lp;
	char **turs;
	char *strng;

	if (!boss || !q)
		return (NULL);

	/* Allocate memory for the array of strings */
	turs = malloc(sizeof(char *) * (q + 1));
	if (!turs)
		return (NULL);

	/* Iterate through the linked list and copy strings to the array */
	for (q = 0; node; node = node->after, q++)
	{
		strng = malloc(_strlen_(node->rop) + 1);
		if (!strng)
		{
			for (lp = 0; lp < q; lp++)
				free(turs[lp]);
			free(turs);
			return (NULL);
		}

		strng = _strcpy_(strng, node->rop);
		turs[q] = strng;
	}
	turs[q] = NULL;
	return (turs);
}


/**
 * output_register - Prints all elements of a regis_t linked list
 *
 * @md: Pointer to the first node.
 *
 * Return: size of the register.
 */
size_t output_register(const regis_t *md)
{
	size_t w = 0;

	while (md)
	{
		_puts_(change_numz(md->figure, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts_(md->rop ? md->rop : "(nil)");/* Print the 'str' element or "(nil)" */
		_puts_("\n");
		md = md->after;
		w++;
	}
	return (w);
}

/**
 * node_begin_on - Returns the node whose string starts with a given prefix.
 *
 * @apex: Pointer to the list head.
 * @mix: String to match.
 * @cht: The next character after prefix to match
 *
 * Return: Match node or null after execution
 */
regis_t *node_begin_on(regis_t *apex, char *mix, char cht)
{
	char *pin = NULL;

	while (apex)
	{
		pin = begin_on(apex->rop, mix);
		if (pin && ((cht == -1) || (*pin == cht)))
			return (apex);
		apex = apex->after;
	}
	return (NULL);
}

/**
 * bring_node_roll - Gets the index of a node in a linked list
 *
 * @front: Pointer to list the front
 * @apex: Pointer to the apex
 *
 * Return: Index of the node or -1 if not found after execution.
 */
ssize_t bring_node_roll(regis_t *front, regis_t *apex)
{
	size_t g = 0;

	while (front)
	{
		if (front == apex)
			return (g);
		front = front->after;
		g++;
	}
	return (-1);/* Node not found in the list */
}

