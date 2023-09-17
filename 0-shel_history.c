#include "function.h"

/**
 * get_history_file - Generates the path for the history file.
 *
 * @update: Pointer to the info_t struct containing information.
 *
 * Return: Allocated string containing history file path or NULL on failure.
 */

char *get_history_file(update_p *update)
{
	char *bufa;
	char *direct;

	direct = _getenv(update, "HOME=");/*Get user's home directory*/
	if (!direct)
		return (NULL);
	bufa = malloc(sizeof(char) * (_strlen_(direct) + _strlen_(HIST_FILE) + 2));
	if (!bufa)
		return (NULL);
	bufa[0] = 0;
	_strcpy_(bufa, direct);
	_strcat_(bufa, "/");
	_strcat_(bufa, HIST_FILE);/*Concatenate home dir path with history file name*/
	return (bufa);
}

/**
 * write_history - Writes history entries to a file.
 *
 * @update: Pointer to the info_t struct containing history information.
 *
 * Return: 1 on success, -1 on failure.
 */
int write_history(update_p *update)
{
	ssize_t fildes;
	char *box_name = get_history_file(update);
	list_t *node = NULL;

	if (!box_name)
		return (-1);

	fildes = open(box_name, O_CREAT | O_TRUNC | O_RDWR, 0644);/*Open history fil*/
	free(box_name);
	if (fildes == -1)
		return (-1);
	for (node = update->history; node; node = node->next)/*Write history entries*/
	{
		_puts_fildes(node->str, fildes);
		_putfildes('\n', fildes);
	}
	_putfildes(BUF_FLUSH, fildes);/*Flush the output buffer*/
	close(fildes);
	return (1);
}

/**
 * read_history - Reads history entries from a file.
 *
 * @update: Pointer to the update_p struct containing history information.
 *
 * Return: Number of history entries read, or 0 on failure.
 */
int read_history(update_p *update)
{
	int gh, last = 0;
	int rulecount = 0;
	ssize_t fildes, read_lengt;
	ssize_t fsize = 0;
	struct stat st;
	char *bufa = NULL, *box_name = get_history_file(update);

	if (!box_name)
		return (0);

	fildes = open(box_name, O_RDONLY);/*OPen history file for reading*/
	free(box_name);
	if (fildes == -1)
		return (0);
	if (!fstat(fildes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	bufa = malloc(sizeof(char) * (fsize + 1));/*Allocate bufa for reading*/
	if (!bufa)
		return (0);
	read_lengt = read(fildes, bufa, fsize);/*Read file into bufa*/
	bufa[fsize] = 0;
	if (read_lengt <= 0)
		return (free(bufa), 0);
	close(fildes);
	for (gh = 0; gh < fsize; gh++)/*Parse & build history list from read bufa*/
		if (bufa[gh] == '\n')
		{
			bufa[gh] = 0;
			build_history_list(update, bufa + last, rulecount++);
			last = gh + 1;
		}
	if (last != gh)
		build_history_list(update, bufa + last, rulecount++);
	free(bufa);
	update->histcount = rulecount;
	while (update->histcount-- >= HIST_MAX)/*Trim hist list if exceeds max*/
		delete_node_at_index(&(update->history), 0);
	renumber_history(update);/*Renumber the history list*/
	return (update->histcount); }

/**
 * build_history_list - Adds entry to the history linked list.
 *
 * @update: - Pointer to the update_p struct containing history information.
 * @bufa: The history entry to add.
 * @cordcount: The line count of the history entry.
 *
 * Return: Always 0 after execution.
 */
int build_history_list(update_p *update, char *bufa, int cordcount)
{
	list_t *node = NULL;

	if (update->history)
		node = update->history;
	add_node_end(&node, bufa, cordcount);

	if (!update->history)
		update->history = node;
	return (0);
}

/**
 * renumber_history - When chenage is complete renumber the history link list.
 *
 * @update: Pointer to the update_p struct containing history information.
 *
 * Return: The new histcount (number of history entries).
 */
int renumber_history(update_p *update)
{
	list_t *node = update->history;
	int gh = 0;

	while (node)
	{
		node->num = gh++;
		node = node->next;
	}
	return (update->histcount = gh);
}
