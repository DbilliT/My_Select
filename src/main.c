#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_select.h"
#include "my.h"

void	linked_free(t_file *list)
{
  if (list == NULL)
    return;
  linked_free(list->next);
  free(list);
}

void	echo_error(char *str, int len)
{
  if (write(2, str, len) == -1)
    return;
}

int		main(int argc, char **argv)
{
  t_file	*list;
  int		main_loop_exit;
  SCREEN	*term;

  if (argc > 1)
    {
      term = term_init();
      list = list_init(argc - 1, argv + 1);
      if (!display_screen(list, NULL, 0, 1))
	{
	  main_loop_exit = main_loop(&list);
	  endwin();
	  if (main_loop_exit == 10 || main_loop_exit == 13)
	    echo_selection(list);
	}
      else
	{
	  endwin();
	  echo_error("Screen too small, couldn't start the program\n", 45);
	}
      linked_free(list);
      delscreen(term);
    }
  return (0);
}
