#include "function.h"

/**
 * _funcputs - Prints an input string to stderr.
 *
 * @strn: the string to be printed
 *
 * Return: Nothing after execution
 */
void _funcputs(char *strn)
{
	int d = 0;

	if (!strn)
		return;

/*Loop through the string and print each character using _eputchar*/
	while (strn[d] != '\0')
	{
		_funcputchar(strn[d]);
		d++;
	}
}

/**
 * _funcputchar - Writes the character c to standerr.
 *
 * @ch: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, & error num is set appropriately.
 */
int _funcputchar(char ch)
{
	static int v;
	static char buf[WRITE_BUF_SIZE];

/*If buffer is full or BUF_FLUSH character is encountered, flush buffer*/
	if (ch == BUF_FLUSH || v >= WRITE_BUF_SIZE)
	{
		write(2, buf, v);
		v = 0;
	}

/* Store character in the buffer */
	if (ch != BUF_FLUSH)
		buf[v++] = ch;
	return (1);
}

/**
 * _putfildes - Writes the character c to the given file descriptor.
 *
 * @chr: The character to print
 * @fildes: The file descriptor which is to written
 *
 * Return: On success 1.
 * On error, -1 is returned, and error num is set appropriately.
 */
int _putfildes(char chr, int fildes)
{
	static int b;
	static char buf[WRITE_BUF_SIZE];

/*If buffer is full or BUF_FLUSH character is encountered, flush buffer*/
	if (chr == BUF_FLUSH || b >= WRITE_BUF_SIZE)
	{
		write(fildes, buf, b);
		b = 0;
	}
/* Store character in the buffer */
	if (chr != BUF_FLUSH)
		buf[b++] = chr;
	return (1);
}

/**
 * _puts_fildes - Prints an input string to the specified file descriptor.
 *
 * @strn: The string to be printed
 * @fildes: The file descriptor which is to written
 *
 * Return: The number of char put.
 */
int _puts_fildes(char *strn, int fildes)
{
	int v = 0;

	if (!strn)
		return (0);
/*Loop through the string and print each character using _putfildes*/
	while (*strn)
	{
		v += _putfildes(*strn++, fildes);
	}
	return (v);
}

