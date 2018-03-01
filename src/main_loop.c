#include <stdlib.h>
#include <ncurses.h>
#include "my_select.h"
#include "my.h"

void		do_search(char *search, int c, t_file *list, int *pos)
{
  int		len;
  int		spos;
  t_file	*copy;

  copy = list;
  spos = 0;
  len = my_strlen(search);
  if (c == 360 && len != 0)
    search[len = len - 1] = '\0';
  else if (c >= 32 && c <= 254 && len < 254)
    {
      search[len] = c;
      search[len = len + 1] = '\0';
    }
  while (copy != NULL && my_strncmp(search, copy->file_name, len))
    {
      copy = copy->next;
      spos = spos + 1;
    }
  if (copy != NULL)
    *pos = spos;
  display_screen(list, search, *pos, 1);
}

void	do_select(t_file *list, int *pos, char *search, int c)
{
  if (c == 32)
    {
      affect_linked(list, *pos);
      cursor_move(pos, KEY_DOWN, count_linked(list));
      display_screen(list, search, *pos, 1);
    }
}

void	do_delete(t_file **list, int *pos, char *search, int c)
{
  if (c == KEY_BACKSPACE || c == KEY_DC)
    {
      delete_linked(*list, list, pos);
      display_screen(*list, search, *pos, 1);
    }
}

int     main_loop(t_file **lst)
{
  int   c;
  int   pos;
  char	*s;

  pos = 0;
  if ((s = malloc(255 * sizeof(char))) == NULL)
    return (27);
  s[0] = '\0';
  while ((c = getch()))
    {
      if (c == KEY_UP || c == KEY_LEFT || c == KEY_RIGHT || c == KEY_DOWN)
	display_screen(*lst, s, cursor_move(&pos, c, count_linked(*lst)), 0);
      do_select(*lst, &pos, s, c);
      do_delete(lst, &pos, s, c);
      if (c == KEY_RESIZE)
	display_screen(*lst, s, pos, 1);
      if (c == 27 || c == 10 || c == 13)
	{
	  free(s);
	  return (c);
	}
      if ((c >= 33 && c <= 254) || c == 360)
	do_search(s, c, *lst, &pos);
    }
  return (0);
}
