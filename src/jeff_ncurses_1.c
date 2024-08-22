#include <ncurses.h>
#include <jeff/jeff_ncurses.h>

void printing(void) {
  addstr("Printed using addstr.\n\n");
  refresh();

  addstr("Using addchr:- ");
  addch('a');
  refresh();

  printw("\n\nPrinted these nums with printw: %d %d %f\n", 150, -12, 12.5555);
  refresh();
}

void moving_and_sleeping(void) {
  int row = 5, col = 0;

  curs_set(0);

  for (char c = 65; c <= 90; c++) {
    move(row++, col++);
    addch(c);
    refresh();
    napms(100);
  }

  row = 5;
  col = 3;

  for (char c = 97; c <= 122; c++) {
    mvaddch(row++, col++, c);
    refresh();
    napms(100);
  }

  curs_set(1);
  addch('\n');
}

void colourizing(void) {
  if (has_colors() && start_color() == OK) {
    init_pair(1, COLOR_YELLOW, COLOR_RED);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_MAGENTA, COLOR_CYAN);

    attrset(COLOR_PAIR(1));
    addstr("Yellow and red\n\n");
    refresh();
    attroff(COLOR_PAIR(1));

    attrset(COLOR_PAIR(2) | A_BOLD);
    addstr("Green and green A_BOLD\n\n");
    refresh();
    attroff(COLOR_PAIR(2));
    attroff(A_BOLD);

    attrset(COLOR_PAIR(3));
    addstr("Magenta and cyan\n");
    refresh();
    attroff(COLOR_PAIR(3));
  } else if (has_colors()) {
    addstr("Cannot start colours\n");
    refresh();
  } else {
    addstr("Not colour capable\n");
    refresh();
  }
}

int main(void) {
  initscr();

  addstr("\nPress any key: ");
  getch();

  endwin();

  printing();
  moving_and_sleeping();
  colourizing();

  return 0;
}

/// vim:ts=2:sts=2:sw=2:et:ai:si:sta:noci:nopi:
