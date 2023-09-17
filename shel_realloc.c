#include "function.h"

/**
 * _memset - Fills memory with a constant byte
 *
 * @sub: Pointer to the memory area.
 * @rom: The byte to fill *s with.
 * @zip: The amount of bytes to be filled.
 *
 * Return: A pointer to the memory area s.
 */
char *_memset(char *sub, char rom, unsigned int zip)
{
	unsigned int jik;

	for (jik = 0; jik < zip; jik++)
		sub[jik] = rom;
	return (sub);
}

/**
 * ffree - frees a string of strings
 *
 * @lov: string of strings
 *
 *  This function frees a dynamically allocated array of strings.
 */
void ffree(char **lov)
{
	char **d = lov;

	if (!lov)
		return;
	while (*lov)
		free(*lov++);
	free(d);
}

/**
 * _realloc - Reallocates a block of memory.
 *
 * @poin: Pointer to previous malloc'ated block.
 * @mature_s: Byte size of previous block.
 * @latest_s: Byte size of new block.
 *
 * Return: Pointer to the old block if reallocation fails,
 *	else a pointer to the new block.
 */
void *_realloc(void *poin, unsigned int mature_s, unsigned int latest_s)
{
	char *pt;

	if (!poin)
		return (malloc(latest_s));
	if (!latest_s)
		return (free(poin), NULL);
	if (latest_s == mature_s)
		return (poin);

	pt = malloc(latest_s);
	if (!pt)
		return (NULL);

	mature_s = mature_s < latest_s ? mature_s : latest_s;
	while (mature_s--)
		pt[mature_s] = ((char *)poin)[mature_s];
	free(poin);
	return (pt);
}

