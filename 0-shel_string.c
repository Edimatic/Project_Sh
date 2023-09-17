#include "function.h"

/**
 * _strlen_ - Computes the length of a string.
 *
 * @man: The string whose length is to be calculated.
 *
 * Return: The integer length of the string.
 */
int _strlen_(char *man)
{
	int suf = 0;

	if (!man)
		return (0);

	while (*man++)/* Incrementally traverse the string */
		suf++;
	return (suf);
}

/**
 * _strcmp_ - Compares two strings lexicographically.
 *
 * @org: The first strang.
 * @mrk: The second strang.
 *
 * Return: negative if org < mrk, positive if org > mrk, zero if org == mrk
 * after execution.
 */
int _strcmp_(char *org, char *mrk)
{
	while (*org && *mrk)/* Compare characters until end of one of the strings */
	{
		if (*org != *mrk)
			return (*org - *mrk);
		org++;
		mrk++;
	}
	if (*org == *mrk)/* Check if both strings ended at the same time (equal) */
		return (0);
	else
		return (*org < *mrk ? -1 : 1);/*Return neg if org < mrk, posiif org > mrk*/
}

/**
 * begin_on - Checks if one string starts with another.
 *
 * @sheaf: The string to be looked for.
 * @stylus: The substring to be discover.
 *
 * Return: Address of the next character in sheaf or NULL if not found.
 */
char *begin_on(const char *sheaf, const char *stylus)
{
	while (*stylus)/* Check each character in the needle */
	{
		if (*stylus++ != *sheaf++)/* If characters are different, return NULL */
			return (NULL);
	}
	return ((char *)sheaf);/* Return address of the next character in haystack */
}

/**
 * *_strcat_ - Concatenates two strings as given.
 *
 * @station: The station buffa
 * @origin: The origin buffa
 *
 * Return: Pointer to stationed bufa after execution.
 */
char *_strcat_(char *station, char *origin)
{
	char *eddy = station;

	while (*station)/* Move station to the end of the string */
		station++;

	while (*origin)/* Copy characters from origin to station */
		*station++ = *origin++;

	*station = *origin;/* Append a null-terminator to the concatenated string */

	return (eddy);/* Return the pointer to the station buffer */
}
