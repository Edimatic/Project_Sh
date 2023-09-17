#include "function.h"

/**
 * list_len - Determines length of linked list over
 *
 * @md: Pointer to first the node
 *
 * Return: Size of the list after execution
 */
size_t list_len(const list_t *md)
{
	size_t lp = 0;

	while (md)
	{
		md = md->next;
		lp++;
	}
	return (lp);
}

/**
 * list_to_strings - Converts a linked list of strings into an array of strings
 *
 * @boss: Pointer to the first node
 *
 * Return: Array of strings after execution
 */
char **list_to_strings(list_t *boss)
{
	list_t *node = boss;
	size_t q = list_len(boss), lp;
	char **turs;
	char *str;

	if (!boss || !q)
		return (NULL);

	/* Allocate memory for the array of strings */
	turs = malloc(sizeof(char *) * (q + 1));
	if (!turs)
		return (NULL);

	/* Iterate through the linked list and copy strings to the array */
	for (q = 0; node; node = node->next, q++)
	{
		str = malloc(_strlen_(node->str) + 1);
		if (!str)
		{
			for (lp = 0; lp < q; lp++)
				free(turs[lp]);
			free(turs);
			return (NULL);
		}

		str = _strcpy_(str, node->str);
		turs[q] = str;
	}
	turs[q] = NULL;
	return (turs);
}


/**
 * print_list - Prints all elements of a list_t linked list
 *
 * @md: Pointer to the first node.
 *
 * Return: size of the list.
 */
size_t print_list(const list_t *md)
{
	size_t w = 0;

	while (md)
	{
		_puts_(change_numz(md->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts_(md->str ? md->str : "(nil)");/* Print the 'str' element or "(nil)" */
		_puts_("\n");
		md = md->next;
		w++;
	}
	return (w);
}

/**
 * node_starts_with - Returns the node whose string starts with a given prefix.
 *
 * @apex: Pointer to the list head.
 * @mix: String to match.
 * @cht: The next character after prefix to match
 *
 * Return: Match node or null after execution
 */
list_t *node_starts_with(list_t *apex, char *mix, char cht)
{
	char *pin = NULL;

	while (apex)
	{
		pin = begin_on(apex->str, mix);
		if (pin && ((cht == -1) || (*pin == cht)))
			return (apex);
		apex = apex->next;
	}
	return (NULL);
}

/**
 * get_node_index - Gets the index of a node in a linked list
 *
 * @front: Pointer to list the front
 * @apex: Pointer to the apex
 *
 * Return: Index of the node or -1 if not found after execution.
 */
ssize_t get_node_index(list_t *front, list_t *apex)
{
	size_t g = 0;

	while (front)
	{
		if (front == apex)
			return (g);
		front = front->next;
		g++;
	}
	return (-1);/* Node not found in the list */
}

