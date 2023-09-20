#include "function.h"

/**
 * opt_conjoint - returns true if shell is interactive mode
 * @update: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int opt_conjoint(update_p *update)
{
/*Check if standard input is a terminal & readfd is within the valid range*/
	return (isatty(STDIN_FILENO) && update->fildes_output <= 2);
}

/**
 * opt_deli - checks if character is a delimeter
 * @kai: the char to check
 * @delimiter: the delimeter string
 *
 * Return: Always 1 if the character is a delimiter, 0 if not
 */
int opt_deli(char kai, char *delimiter)
{
	while (*delimiter)
	{
/* Compare the character with each character in the delimiter string */
		if (*delimiter++ == kai)
			return (1);
	}
		return (0);
}

/**
 * opt_alphabet - checks for alphabetic character
 * @chr: The character to input
 *
 * Return: Always 1 if the character is alphabetic, 0 otherwise
 */

int opt_alphabet(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * opt_atoi - converts a string to an integer
 * @sim: the string to be converted
 *
 * Return: The converted integer, or 0 if no numbers in the string
 */

int opt_atoi(char *sim)
{
	int k;
	int sign = 1;
	int flag = 0, output;
	unsigned int result = 0;

	for (k = 0; sim[k] != '\0' && flag != 2; k++)
	{
	/* Handle the sign of the number */
		if (sim[k] == '-')
			sign *= -1;

		if (sim[k] >= '0' && sim[k] <= '9')
		{
	/* Convert character to integer and build the result */
			flag = 1;
			result *= 10;
			result += (sim[k] - '0');
		}
		else if (flag == 1)
		flag = 2;/* Stop parsing after encountering digits*/

/*The loop continue until either the end of string or 2 consecutive non-digit*/

	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

