#include <stdlib.h>
#include <ncurses.h>
#include "my_select.h"
#include "my.h"

void	display_selected(t_file *list, char *search)
{
  int   rc[2];
  int	count;

  getmaxyx(stdscr, rc[0], rc[1]);
  count = 0;
  while (list != NULL)
    {
      if (list->selected)
	count = count + 1;
      list = list->next;
    }
  attron(A_REVERSE);
  if (search != NULL && search[0] != '\0')
    mvprintw(rc[0] - 1, 0, "Search: %s", search);
  if (count != 0)
    mvprintw(rc[0] - 1, rc[1] - (12 + (count / 100)), "Selected: %d", count);
  attroff(A_REVERSE);
}

int	display_file(t_file *list, int cursor, int i, int pad)
{
  int   rc[2];

  getmaxyx(stdscr, rc[0], rc[1]);
  if (pad + my_strlen(list->file_name) > rc[1])
    {
      clear();
      mvprintw(0, 0, "Couldn't display everything, screen too small.");
      return (0);
    }
  if (list->selected)
    attron(A_REVERSE);
  if (i == cursor)
    attron(A_UNDERLINE);
  mvprintw(i % (rc[0] - 2), pad, "%s", list->file_name);
  if (i == cursor)
    attroff(A_UNDERLINE);
  if (list->selected)
    attroff(A_REVERSE);
  return (1);
}

int	display_list(int i, t_file *list, int cursor, int *max_len)
{
  int	rc[2];

  getmaxyx(stdscr, rc[0], rc[1]);
  if (i % (rc[0] - 2) == 0)
    {
      max_len[0] = max_len[0] + max_len[1];
      max_len[1] = 0;
    }
  if (my_strlen(list->file_name) > max_len[1])
    max_len[1] = my_strlen(list->file_name) + 4;
  if (!display_file(list, cursor, i, max_len[0]))
    return (1);
  return (0);
}

int	display_screen(t_file *list, char *search,
		       int cursor, int need_clear)
{
  int	i;
  int	max_len[2];

  i = 0;
  max_len[0] = 0;
  max_len[1] = 0;
  if (need_clear)
    clear();
  display_selected(list, search);
  while (list != NULL)
    {
      if (display_list(i, list, cursor, max_len))
	return (1);
      i = i + 1;
      list = list->next;
    }
  refresh();
  return (0);
}
