#define _XOPEN_SOURCE_EXTENDED 1
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <curses.h>
#include "conway.h"

#define BLOCK L'\uE030'
int main(void) {

    WINDOW * mainwin;
    int ch = '0';
    int x = 0;
    int y = 0;
    int cols = 0;
    int rows = 0;
    int width, height = 400;
    char mover = '@';
    char label[45];

    Conway conway = Conway();
    conway.seedTheCanvas();

    bool getValueAtLocation(int x, int y);
    void processNextCycle();

    setlocale(LC_ALL,"en_US.UTF-8");
    /*  Initialize ncurses  */

    if ( (mainwin = initscr()) == NULL ) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    if(has_colors() == FALSE){
        fprintf(stderr, "This program requires color support on the terminal\n");
        exit(EXIT_FAILURE);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);
    init_pair(2, COLOR_MAGENTA, COLOR_CYAN);
    attron(COLOR_PAIR(2));

    printw(" Cellular Automaton - Conway's Game of Life"); 
    getmaxyx(stdscr, rows, cols);
    int spacing = cols - 43;
    for(int i=0; i< spacing; i++){
        printw(" ");
    }
    attroff(COLOR_PAIR(2));
    mvaddch(1,0, ' ');
    attron(COLOR_PAIR(1));
    noecho();
    keypad(mainwin, TRUE);
    

    refresh();
    
    /*  Loop until user hits 'q' to quit  */
    while ( (ch = getch()) != 'q' ) {
        getmaxyx(stdscr, rows, cols);
        sprintf(label, "Rows = %d, Cols = %d",rows, cols);
        printw(label);
        mvaddch(y,x, ' ');
        switch ( ch ) {
            case KEY_UP:
                if ( y > 0 )
                    --y;
                break;

            case KEY_DOWN:
                ++y;
                break;

            case KEY_LEFT:
                if ( x > 0 )
                    --x;
                break;

            case KEY_RIGHT:
                ++x;
                break;

            case 'h':
                x = 0;
                y = 0;
                break;

            case 'e':
                x = (cols - width);
                y = (rows - height);
                break;

        }
        mvaddch(y,x, mover);
        refresh();
    }


    /*  Clean up after ourselves  */
    delwin(mainwin);
    endwin();
    refresh();

    return EXIT_SUCCESS;
}
