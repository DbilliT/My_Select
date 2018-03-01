#include <ncurses.h>

int	move_left(int *rc, int *cur, int elem)
{
  if (*cur - (rc[0] - 2) < 0)
    {
      if ((*cur = elem - (elem % (rc[0] - 2)) + *cur) >= elem)
	*cur = *cur - (rc[0] - 2);
      return (*cur);
    }
  return (*cur = *cur - (rc[0] - 2));
}

int     cursor_move(int *cur, int c, int elem)
{
  int	rc[2];

  getmaxyx(stdscr, rc[0], rc[1]);
  rc[1] = rc[1];
  if (c == KEY_LEFT)
    return (move_left(rc, cur, elem));
  else if (c == KEY_RIGHT)
    {
      if (*cur + (rc[0] - 2) >= elem)
	return (*cur = 0 + *cur % (rc[0] - 2));
      return (*cur = *cur + (rc[0] - 2));
    }
  else if (c == KEY_UP)
    {
      if ((*cur = *cur - 1) < 0)
	return (*cur = elem + *cur);
    }
  else
    return (*cur = (*cur + 1) % elem);
  return (*cur);
}
