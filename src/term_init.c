#include <ncurses.h>
#include <stdlib.h>

void		*term_init(void)
{
  SCREEN	*terminal;

  terminal = newterm(NULL, stderr, stdin);
  terminal = set_term(terminal);
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  return (terminal);
}
