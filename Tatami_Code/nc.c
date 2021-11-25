#include <ncurses.h>
#include <string.h>
#define INPUT_X 5

int main()
{	int ch;
    char vars[64];
    vars[0] = '\0';
    char buffer = 0;
    int end_point = 64;

	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
    move(0, INPUT_X);

    //printw("Type any character to see it in bold\n");
    int j = 0;
    int k = 0;
    for (int i = 0; i < 20; i++) {
	    ch = getch();			/* If raw() hadn't been called
        
					 * we have to press enter before it
					 * gets to the program 		*/
	    if(ch == KEY_LEFT) {
            j = j - 1;
	        mvprintw(3, 0, "You pressed a <-");
            move(0, INPUT_X + j);
            //mvprintw(0, j, "");

        } else {
            k = j;
            while (ch != 0) {
                buffer = vars[k];
                vars[k] = ch;
                ch = buffer;
                k = k + 1;
            }
            vars[k] = '\0';

            //printw("The pressed key is ");
		    //attron(A_BOLD);

		    mvprintw(0, INPUT_X, "%s", vars);
            j++;
	        move(0, INPUT_X + j);
	    }
	    refresh();			/* Print it on to the real screen */
    }
    //getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
