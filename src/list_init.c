#include <stdlib.h>
#include <unistd.h>
#include "my_select.h"

void		create_chained(t_file **head, char *file_name)
{
  t_file	*new;

  if ((new = malloc(sizeof(*new))) != NULL)
    {
      new->file_name = file_name;
      new->selected = 0;
      new->next = *head;
    }
  *head = new;
}

t_file          *list_init(int elements, char **files)
{
  t_file        *head;

  head = NULL;
  while (elements)
    {
      create_chained(&head, files[elements - 1]);
      elements = elements - 1;
    }
  return (head);
}
