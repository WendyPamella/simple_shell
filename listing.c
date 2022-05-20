#include "mainshell.h"

/**
 * add_node_end - adds new node
 * @head: address of first node
 * @name: value of name in new field of new node
 * @value: valiue of field of new node
 *
 * Return: head of new list, NULL if it fails
 */

void free_list(list_t *h)
{
	list_t *current;

	if (h == NULL)
		return;

	while (h != NULL)
	{
		current = h;
		h = h->next;
		free_node(current);
	}
}

void free_node(list_t *h)
{
	if (h == NULL)
		return;

	if (h->name)
		free(h->name);

	if (h->value)
		free(h->value);

	free(h);
	h = NULL;
}

list_t *split_string(char *s, char *delim)
{
	char *str, *next_str;
	list_t *strings = NULL;

	if (s == NULL || delim == NULL || *s == '\0')
	{
		return (NULL);
	}

	str = _strdup(s);

	/* get first string */
	add_node_end(&strings, _strtok(str, delim), "");

	/* get all other strings */
	while ((next_str = _strtok(NULL, delim)))
		add_node_end(&strings, next_str, "");

	free(str);

	return (strings);
}

char **list_to_array(const list_t *h)
{
	char **array;
	unsigned int i, length;

	if (h == NULL)
		return (NULL);

	/* allocate space for array */
	length = list_len(h);
	array = malloc(sizeof(char *) * (length + 1));
	if (array == NULL)
		return (NULL);

	for (i = 0; i < length && h; i++, h = h->next)
		array[i] = _strdup(h->name);

	array[length] = NULL;

	return (array);
}

int find_name(list_t *h, const char *name)
{
	list_t *trav = h;
	int index = 0;

	if (h == NULL || name == NULL)
		return (-1);

	/* find matching node */
	while (trav && (_strcmp(trav->name, name)))
	{
		index++;
		trav = trav->next;
	}

	return (trav ? index : -1);
}

void free_array(char **arr)
{
	unsigned int i;

	for (i = 0; arr && arr[i]; i++)
		free(arr[i]);

	if (arr)
	{
		free(arr);
	}

	arr = NULL;
}

int update_value(list_t *h, int index, const char *value)
{
	list_t *trav = h;

	if (h == NULL || index < 0 || value == NULL)
		return (-1);

	/* find node to update */
	while (index && trav)
	{
		index--;
		trav = trav->next;
	}

	/* update node */
	if (trav)
	{
		free(trav->value);
		trav->value = _strdup(value);
		/*printf("UPDATE SUCCESSFUL!!!!\n");*/
		return (0);
	}

	return (-1);
}

int delete_node_index(list_t **head, int index)
{
	list_t *current, *del;
	int i;


	if (head == NULL || *head == NULL)
		return (-1);

	current = *head;

	if (index == 0)
	{
		*head = (*head)->next;
		free_node(current);
		return (0);
	}

	for (i = 0; (i < index - 1) && current->next; i++)
		current = current->next;

	if (current->next && i == index - 1)
	{
		del = current->next;
		current->next = current->next->next;
		free_node(del);
	}

	return (0);
}
