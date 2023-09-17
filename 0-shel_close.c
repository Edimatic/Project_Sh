#include "function.h"

/**
 **_strncpy_ - Copy a strings to different collcations.
 *
 *@dest: The destinationat which the string to be copied
 *@sou: Location at which source string to copied from
 *@numz: The quantity of characters to be copied from the source.
 *
 *Return: A pointer to the concatenated string.
 */
char *_strncpy_(char *dest, char *sou, int numz)
{
	int y;
	int z;
	char *os = dest;

	y = 0;
/*Copy characters from src to dest until n-1 characters or null-terminator*/
	while (sou[y] != '\0' && y < numz - 1)
	{
		dest[y] = sou[y];
		y++;
	}
	if (y < numz)
	{
		z = y;
	/* Fill the remaining space with null-terminators */
		while (z < numz)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (os);
}

/**
 **_strncat_ - concatenates two strings
 *
 *@dest: The 1st destination string on the segment
 *@sou: The 2nd source string on the segment
 *@numz: The maximum number of bytes to be used.
 *
 *Return: A pointer to the concatenated string.
 */
char *_strncat_(char *dest, char *sou, int numz)
{
	int y;
	int z;
	char *os = dest;

	y = 0;
	z = 0;
/* Find the end of the destination string */
	while (dest[y] != '\0')
		y++;
/*Copy characters from src to dest until n characters or null-terminator*/
	while (sou[z] != '\0' && z < numz)
	{
		dest[y] = sou[z];
		y++;
		z++;
	}
	if (z < numz)
		dest[y] = '\0';/*Ensure null-terminator is added*/
	return (os);
}

/**
 **_strchr_ - Locates a character in a string as posible.
 *
 *@os: The string to be parsed on the program
 *@ch: The character to look for on the program
 *
 *Return: A pointer to the memory area os containing the character ch,
 *		or NULL if not found.
 */
char *_strchr_(char *os, char ch)
{
	do {
		if (*os == ch)
			return (os);
	} while (*os++ != '\0');

	return (NULL);
}

