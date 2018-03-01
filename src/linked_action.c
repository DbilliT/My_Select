#include <stdlib.h>
#include <ncurses.h>
#include "my_select.h"

int     count_linked(t_file *list)
{
  int   count;

  count = 0;
  while (list != NULL)
    {
      count = count + 1;
      list = list->next;
    }
  return (count);
}

void    affect_linked(t_file *list, int position)
{
  int   i;

  i = 0;
  while (i != position)
    {
      i = i + 1;
      list = list->next;
    }
  list->selected = !list->selected;
}

void            first_delete(t_file **list)
{
  t_file        *head;

  head = *list;
  *list = (*list)->next;
  free(head);
}

void            delete_linked(t_file *list, t_file **adress, int *position)
{
  int           i;
  t_file        *elem;

  i = 0;
  if (list->next == NULL)
    {
      endwin();
      exit(1);
    }
  if (!(*position))
    {
      first_delete(adress);
      return;
    }
  while (i < *position - 1)
    {
      i = i + 1;
      list = list->next;
    }
  elem = list->next;
  list->next = list->next->next;
  free(elem);
  if (list->next == NULL)
    *position = *position - 1;
}
