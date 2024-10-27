#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define FOREVER 1
#define HEIGHT_GAME 17
#define WIDTH_GAME 33
void print_in_middle(WINDOW *win, int starty, int startx, int width,
                     char *string, chtype color) {
  int length, x, y;
  int temp;
  if (win == NULL) win = stdscr;
  getyx(win, y, x);
  if (startx != 0) x = startx;
  if (starty != 0) y = starty;
  if (width == 0) width = 80;
  length = strlen(string);
  temp = (width - length) / 2;
  x = x + temp;
  wattron(win, color);
  mvwprintw(win, y, x, "%s", string);
  wattroff(win, color);
  refresh();
}
void print_menu(WINDOW *menu_window, int highlight, int width) {
  char choices[3][9] = {"New Game", "Resume", "Quit"};
  int i;
  int x = 5, y = 10;
  box(menu_window, 0, 0); 
  mvwprintw(menu_window, 2, x, "                          ____   ___  _  _    ___ ");
  mvwprintw(menu_window, 3, x, "                         |___ | / _ || || |  ( _ )");
  mvwprintw(menu_window, 4, x, "                           __) | | | | || |_ / _ \\ ");
  mvwprintw(menu_window, 5, x, "                          / __/| |_| |__   _| (_) |");
  mvwprintw(menu_window, 6, x, "                         |_____| |__/   |_|  \\___/ ");
  for (i = 0; i < 3; i++) {
    int spaces = width - strlen(choices[i]);
    spaces = spaces / 2;
    if (highlight == i + 1) {
      wattron(menu_window, A_REVERSE);
      mvwprintw(menu_window, y,  spaces, "%s", choices[i]);
      wattroff(menu_window, A_REVERSE);

    } else
      mvwprintw(menu_window, y , spaces, "%s", choices[i]);
    ++y;
  }
  wbkgd(menu_window, COLOR_PAIR(2));
  wrefresh(menu_window);
}
void print_pannel(WINDOW *pannel, int *score) {
  time_t now;
  time(&now);
  wrefresh(pannel);
  mvwprintw(pannel, 1, 1, "date and time: %s", ctime(&now));
  mvwprintw(pannel, 2, 1, "score: %d   ", *score);
  mvwprintw(pannel, 3, 1, "commands: KEY-UP");
  mvwprintw(pannel, 4, 10, " KEY-DOWN");
  mvwprintw(pannel, 5, 10, " KEY-LEFT");
  mvwprintw(pannel, 6, 10, " KEY-RIGHT");
  mvwprintw(pannel, 7, 1, " press 'u' for undo ");
  mvwprintw(pannel, 8, 1, " press 'q' for quit ");
  wbkgd(pannel, COLOR_PAIR(2));
  wrefresh(pannel);
}
void print_number(WINDOW *game, int game_matrix[4][4]) {
  int i, j, k = 2, l = 2;
  int nr = 0, cnt = 0;
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (game_matrix[i][j] != 0) {
        // check how many digits does the number have
        nr = game_matrix[i][j];
        while (nr) {
          nr = nr / 10;
          cnt++;
        }
        if (game_matrix[i][j] == 2) {
          wattron(game, COLOR_PAIR(1));
          mvwprintw(game, k, l, "%d  ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(1));
        }
        if (game_matrix[i][j] == 4) {
          wattron(game, COLOR_PAIR(2));
          mvwprintw(game, k, l, "%d   ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(2));
        }
        if (game_matrix[i][j] == 8) {
          wattron(game, COLOR_PAIR(3));
          mvwprintw(game, k, l, "%d   ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(3));
        }
        if (game_matrix[i][j] == 16) {
          wattron(game, COLOR_PAIR(4));
          mvwprintw(game, k, l, "%d   ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(4));
        }
        if (game_matrix[i][j] == 32) {
          wattron(game, COLOR_PAIR(5));
          mvwprintw(game, k, l, "%d   ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(5));
        }
        if (game_matrix[i][j] == 64) {
          wattron(game, COLOR_PAIR(6));
          mvwprintw(game, k, l, "%d   ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(6));
        }
        if (game_matrix[i][j] == 128) {
          wattron(game, COLOR_PAIR(7));
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(7));
        }
        if (game_matrix[i][j] == 256) {
          wattron(game, COLOR_PAIR(8));
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(8));
        }
        if (game_matrix[i][j] == 512) {
          wattron(game, COLOR_PAIR(9));
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(9));
        }
        if (game_matrix[i][j] == 1024) {
          wattron(game, COLOR_PAIR(10));
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(10));
        }
        if (game_matrix[i][j] == 2048) {
          wattron(game, COLOR_PAIR(11));
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
          wattroff(game, COLOR_PAIR(11));
        }
        if (game_matrix[i][j] > 2048) {
          mvwprintw(game, k, l, "%d    ", game_matrix[i][j]);
        }
        mvwhline(game, 4, 1, ACS_HLINE, WIDTH_GAME - 2);
        mvwhline(game, 8, 1, ACS_HLINE, WIDTH_GAME - 2);
        mvwhline(game, 12, 1, ACS_HLINE, WIDTH_GAME - 2);

        mvwvline(game, 1, 8, ACS_VLINE, HEIGHT_GAME - 2);
        mvwvline(game, 1, 16, ACS_VLINE, HEIGHT_GAME - 2);
        mvwvline(game, 1, 24, ACS_VLINE, HEIGHT_GAME - 2);
      } else
        mvwprintw(game, k, l, "    ");
      l = l + 8 - nr;
    }
    k = k + 4;
    l = 2;
  }
  box(game, 0, 0);
  wrefresh(game);
}
void random_number(int game_matrix[4][4]) {
  int i, j, k = 0;
  int empty[16][2] = {0};
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      if (game_matrix[i][j] == 0) {
        empty[k][0] = i;
        empty[k][1] = j;
        k++;
      }
  if (k != 0) {
    srand(time(NULL));
    // selecting a random position
    int poz_random = rand() % k;
    int m = empty[poz_random][0];
    int n = empty[poz_random][1];
    int value = rand() % 3;
    // choosing a random number and putting 2 or 4
    if (value == 0 || value == 1)
      game_matrix[m][n] = 2;
    else if (value == 2)
      game_matrix[m][n] = 4;
  }
}
void move_down(int game_matrix[4][4], int *score) {
  int i, j, k;
  for (j = 0; j < 4; j++) {
    for (i = 2; i >= 0; i--) {
      // moving al the non-zero elements to the bottom
      if (game_matrix[i][j] != 0) {
        k = i;
        while (k < 3 && game_matrix[k + 1][j] == 0) {
          game_matrix[k + 1][j] = game_matrix[k][j];
          game_matrix[k][j] = 0;
          k++;
        }
      }
    }

    for (i = 2; i >= 0; i--) {
      // uniting all equal numbers and moving the rest downwards
      if (game_matrix[i + 1][j] == game_matrix[i][j]) {
        game_matrix[i + 1][j] = 2 * game_matrix[i][j];
        *score = *score + game_matrix[i + 1][j];
        game_matrix[i][j] = 0;
        k = i;
        while (k > 0 && game_matrix[k + 1][j] != 0) {
          game_matrix[k][j] = game_matrix[k - 1][j];
          game_matrix[k - 1][j] = 0;
          k--;
        }
      }
    }
  }
}
void move_up(int game_matrix[4][4], int *score) {
  int i, j, k;
  for (j = 0; j < 4; j++) {
    for (i = 1; i < 4; i++) {
      // moving al the non-zero elements to the bottom
      if (game_matrix[i][j] != 0) {
        k = i;
        while (k > 0 && game_matrix[k - 1][j] == 0) {
          game_matrix[k - 1][j] = game_matrix[k][j];
          game_matrix[k][j] = 0;
          k--;
        }
      }
    }
    for (i = 1; i < 4; i++) {
      if (game_matrix[i][j] == game_matrix[i - 1][j]) {
        game_matrix[i - 1][j] = 2 * game_matrix[i][j];
        *score = *score + game_matrix[i - 1][j];
        game_matrix[i][j] = 0;
        k = i;
        while (k < 3 && game_matrix[k - 1][j] != 0) {
          game_matrix[k][j] = game_matrix[k + 1][j];
          game_matrix[k + 1][j] = 0;
          k++;
        }
      }
    }
  }
}
void move_left(int game_matrix[4][4], int *score) {
  int i, j, k;
  for (i = 0; i < 4; i++) {
    // moving al the non-zero elements to the left
    for (j = 1; j < 4; j++) {
      if (game_matrix[i][j] != 0) {
        k = j;
        while (k > 0 && game_matrix[i][k - 1] == 0) {
          game_matrix[i][k - 1] = game_matrix[i][k];
          game_matrix[i][k] = 0;
          k--;
        }
      }
    }
    // uniting equal elements and moving the rest to the left
    for (j = 1; j < 4; j++) {
      if (game_matrix[i][j] == game_matrix[i][j - 1]) {
        game_matrix[i][j - 1] = 2 * game_matrix[i][j - 1];
        game_matrix[i][j] = 0;
        *score = *score + game_matrix[i][j - 1];
      }
      if (game_matrix[i][j] == 0) {
        k = j;
        while (k < 3 && game_matrix[i][k + 1] != 0) {
          game_matrix[i][k] = game_matrix[i][k + 1];
          game_matrix[i][k + 1] = 0;
          k++;
        }
      }
    }
  }
}
void move_right(int game_matrix[4][4], int *score) {
  int i, j, k;
  for (i = 0; i < 4; i++) {
    // moving al the non-zero elements to the right
    for (j = 2; j >= 0; j--) {
      if (game_matrix[i][j] != 0) {
        k = j;
        while (k < 3 && game_matrix[i][k + 1] == 0) {
          game_matrix[i][k + 1] = game_matrix[i][k];
          game_matrix[i][k] = 0;
          k++;
        }
      }
    }
    // uniting equal elements and moving the rest to the right
    for (j = 2; j >= 0; j--) {
      if (game_matrix[i][j] == game_matrix[i][j + 1]) {
        game_matrix[i][j + 1] = 2 * game_matrix[i][j];
        game_matrix[i][j] = 0;
        *score = *score + game_matrix[i][j + 1];

        k = j;
        while (k > 0 && game_matrix[i][k - 1] != 0) {
          game_matrix[i][k] = game_matrix[i][k - 1];
          game_matrix[i][k - 1] = 0;
          k--;
        }
      }
    }
  }
}
void check_winner(int game_matrix[4][4], WINDOW *winner) {
  int i, j, ok = 0, ok_vertical = 0, ok_oriz = 0, ok_dif = 0;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      if (game_matrix[i][j] == 2048) ok++;
      if (game_matrix[i][j] != 0) ok_dif++;
    }
  if (ok_dif == 16) {
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++) {
        if (game_matrix[i][j] != 0) {
          if (game_matrix[i][j] == game_matrix[i + 1][j]) ok_vertical++;
          if (game_matrix[i][j] == game_matrix[i][j + 1]) ok_oriz++;
        }
      }
  }
  if (ok == 1) {
    box(winner, 0, 0);
    mvwprintw(winner, 1, 1, " you win!");
    wrefresh(winner);
  }
  if (ok_dif == 16) {
    if ((ok_vertical == 0) && (ok_oriz == 0)) {
      box(winner, 0, 0);
      mvwprintw(winner, 1, 7, " game over:(");
      wrefresh(winner);
    }
  }
}
void move_alone(int game_matrix[4][4], int *score, WINDOW *game, WINDOW *pannel,
                WINDOW *winner) {
  int i, j, k;
  int empty[4] = {0}, max = 0;
  int copy1_matrix[4][4], copy2_matrix[4][4];
  int copy3_matrix[4][4], copy4_matrix[4][4];
  int score1, score2, score3, score4;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      copy1_matrix[i][j] = game_matrix[i][j];
      copy2_matrix[i][j] = game_matrix[i][j];
      copy3_matrix[i][j] = game_matrix[i][j];
      copy4_matrix[i][j] = game_matrix[i][j];
    }

  k = 0;
  move_up(copy1_matrix, &score1);
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      // check if the copied and moved matrix is equal 
      // to the initial matrix 
      // using k to count the elements that are equal
      if (copy1_matrix[i][j] == game_matrix[i][j]) k++;
    }
  // if the matrixes are equal, the move is not valid
  if (k == 16) empty[0] = 0;
  // if the matrixes are not equal, the move is valid and
  // i count how many zeros are in the copy after the movement
  else
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++) {
        if (copy1_matrix[i][j] == 0) empty[0]++;
      }

  k = 0;
  move_down(copy2_matrix, &score2);
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      if (copy1_matrix[i][j] == game_matrix[i][j]) k++;
    }
  if (k == 16)
    empty[1] = 0;
  else
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++) {
        if (copy2_matrix[i][j] == 0) empty[1]++;
      }

  k = 0;
  move_left(copy3_matrix, &score3);
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      if (copy3_matrix[i][j] == game_matrix[i][j]) k++;
    }
  if (k == 16)
    empty[2] = 0;
  else {
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++) {
        if (copy3_matrix[i][j] == 0) empty[2]++;
      }
  }

  k = 0;
  move_right(copy4_matrix, &score4);
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++) {
      if (copy4_matrix[i][j] == game_matrix[i][j]) k++;
    }
  if (k == 16)
    empty[3] = 0;
  else {
    for (i = 0; i < 4; i++)
      for (j = 0; j < 4; j++) {
        if (copy4_matrix[i][j] == 0) k++;
      }
  }

  for (i = 0; i < 4; i++) {
    if (empty[i] >= max) max = empty[i];
  }
  if (max == empty[0]) move_up(game_matrix, score);
  if (max == empty[1]) move_down(game_matrix, score);
  if (max == empty[2]) move_left(game_matrix, score);
  if (max == empty[3]) move_right(game_matrix, score);
  print_number(game, game_matrix);
  print_pannel(pannel, score);

  random_number(game_matrix);
  print_number(game, game_matrix);

  check_winner(game_matrix, winner);
}
void newgame(int game_matrix[4][4], int *score, WINDOW *game, WINDOW *pannel,
             WINDOW *winner, WINDOW *menu_window, int highlight, int width) {
  clear();
  int i, j, k;
  int score_copy;
  int matrix_copy[4][4] = {0};
  int undo_copy[4][4] = {0};
  int score_undo = 0;
  box(game, 0, 0);

  mvwhline(game, 4, 1, ACS_HLINE, WIDTH_GAME - 2);
  mvwhline(game, 8, 1, ACS_HLINE, WIDTH_GAME - 2);
  mvwhline(game, 12, 1, ACS_HLINE, WIDTH_GAME - 2);

  mvwvline(game, 1, 8, ACS_VLINE, HEIGHT_GAME - 2);
  mvwvline(game, 1, 16, ACS_VLINE, HEIGHT_GAME - 2);
  mvwvline(game, 1, 24, ACS_VLINE, HEIGHT_GAME - 2);

  box(pannel, 0, 0);
  wrefresh(game);
  print_pannel(pannel, score);

  print_number(game, game_matrix);
  wrefresh(game);
  keypad(game, TRUE);
  int c = wgetch(game);
  wtimeout(game, 10000);
  while (FOREVER) {
    if (c != ERR) {
      // move all the squares UP
      if (c == KEY_UP) {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            matrix_copy[i][j] = game_matrix[i][j];
          }
        k = 0;
        move_up(matrix_copy, &score_copy);
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            if (game_matrix[i][j] == matrix_copy[i][j]) k++;
          }
        if (k != 16) {
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++) undo_copy[i][j] = game_matrix[i][j];
          score_undo = *score;
          move_up(game_matrix, score);
          print_number(game, game_matrix);
          print_pannel(pannel, score);

          random_number(game_matrix);
          print_number(game, game_matrix);

          check_winner(game_matrix, winner);
        }
      }
      // move all the squares DOWN
      if (c == KEY_DOWN) {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            matrix_copy[i][j] = game_matrix[i][j];
          }
        k = 0;
        move_down(matrix_copy, &score_copy);
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            if (game_matrix[i][j] == matrix_copy[i][j]) k++;
          }
        if (k != 16) {
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++) undo_copy[i][j] = game_matrix[i][j];
          score_undo = *score;
          move_down(game_matrix, score);
          print_number(game, game_matrix);
          print_pannel(pannel, score);

          random_number(game_matrix);
          print_number(game, game_matrix);

          check_winner(game_matrix, winner);
        }
      }
      // move all the squares to the LEFT
      if (c == KEY_LEFT) {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            matrix_copy[i][j] = game_matrix[i][j];
          }
        k = 0;
        move_left(matrix_copy, &score_copy);
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            if (game_matrix[i][j] == matrix_copy[i][j]) k++;
          }
        if (k != 16) {
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++) undo_copy[i][j] = game_matrix[i][j];
          score_undo = *score;
          move_left(game_matrix, score);
          print_number(game, game_matrix);
          print_pannel(pannel, score);

          random_number(game_matrix);
          print_number(game, game_matrix);

          check_winner(game_matrix, winner);
        }
      }
      // move all the squares to the RIGHT
      if (c == KEY_RIGHT) {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            matrix_copy[i][j] = game_matrix[i][j];
          }
        k = 0;
        move_right(matrix_copy, &score_copy);
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) {
            if (game_matrix[i][j] == matrix_copy[i][j]) k++;
          }
        if (k != 16) {
          for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++) undo_copy[i][j] = game_matrix[i][j];
          score_undo = *score;
          move_right(game_matrix, score);
          print_number(game, game_matrix);
          print_pannel(pannel, score);

          random_number(game_matrix);
          print_number(game, game_matrix);

          check_winner(game_matrix, winner);
        }
      }
      if (c == 'u') {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) game_matrix[i][j] = undo_copy[i][j];
        *score = score_undo;
        print_number(game, game_matrix);
        print_pannel(pannel, score);
      }
      if (c == 'q') {
        clear();
        refresh();
        print_menu(menu_window, highlight, width);
        break;
      }
    }
    // if the player didn`t press an arrow for 10 seconds 
    else {
      move_alone(game_matrix, score, game, pannel, winner);
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) undo_copy[i][j] = game_matrix[i][j];
      score_undo = *score;
    }
    c = wgetch(game);
  }
}
int main() {
  WINDOW *menu_window;
  int ymax, xmax;  // length and width of the terminal
  int n_choices = 3;
  int highlight = 0;
  initscr();
  clear();
  noecho();
  curs_set(0);

  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);
  init_pair(8, COLOR_RED, COLOR_BLACK);
  init_pair(9, COLOR_CYAN, COLOR_BLACK);
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);
  init_pair(11, COLOR_GREEN, COLOR_BLACK);
  init_pair(12, COLOR_MAGENTA, COLOR_BLACK);

  getmaxyx(stdscr, ymax, xmax);  // length and width of the terminal
  int height = ymax / 2, width = xmax / 2, starty = ymax / 4, startx = xmax / 4;
  menu_window = newwin(height, width, starty, startx);

  mvwhline(menu_window, 8, 1, ACS_HLINE, width - 2);
  print_menu(menu_window, highlight, width);

  int starty_game = (ymax - HEIGHT_GAME) / 2;
  int startx_game = xmax / 2 - HEIGHT_GAME;
  WINDOW *game = newwin(HEIGHT_GAME, WIDTH_GAME, starty_game, startx_game);
  WINDOW *pannel = newwin(10, 45, 0, xmax - 45);
  WINDOW *winner = newwin(3, WIDTH_GAME, starty_game - 3, startx_game);

  highlight = 1;
  keypad(menu_window, TRUE);
  int game_matrix[4][4] = {0}, s;
  int score = 0;
  int ch;
  ch = wgetch(menu_window);
  int i, j;
  while (ch != 'q') {
    if (ch == KEY_UP) {
      if (highlight == 1) {
        highlight = n_choices;
      } else {
        --highlight;
      }
      print_menu(menu_window, highlight, width);
    }
    if (ch == KEY_DOWN) {
      if (highlight == n_choices) {
        highlight = 1;
      } else {
        highlight++;
      }
      print_menu(menu_window, highlight, width);
    }
    // if i press ENTER
    if (ch == 10) {
      // if i press NEW GAME
      if (highlight == 1) {
        clear();
        refresh();
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) game_matrix[i][j] = 0;
        score = 0;
        random_number(game_matrix);
        random_number(game_matrix);
        newgame(game_matrix, &score, game, pannel, winner, menu_window,
                highlight, width);
      }
      // if i press RESUME
      if (highlight == 2) {
        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++) s = s + game_matrix[i][j];
        if (s != 0) {
          clear();
          refresh();
          newgame(game_matrix, &score, game, pannel, winner, menu_window,
                  highlight, width);
        }
      }
      // if i press ENTER
      if (highlight == 3) break;
    }
    ch = wgetch(menu_window);
  }
  attroff(COLOR_PAIR(1));
  endwin();
  return 0;
}
