#include <ncurses.h>
#include <stdlib.h>

#define DX 3

void PrintText(WINDOW *win, FILE* file, int i){
	char str[80];
	box(win, 0, 0); 
    wmove(win, 1, 0); 
    int count = 0;
    i = i * (LINES-2*DX - 2);
	while(count != (LINES-2*DX - 2) && fgets(str, 80, file)) {
        wprintw(win, "  %d %s", i, str);
        box(win, 0, 0); 
        wrefresh(win);
        i++;
        count++;
    }
}

int main(int argc, char* argv[]){
	if(argc < 2){
		printf("No file name was provided.");
		exit(1);
	}

	initscr();
	noecho();
    cbreak();
    printw("File: %s", argv[1]);
    refresh();

    WINDOW *win;
	win = newwin(LINES-2*DX, COLS-2*DX, DX, DX);
	
	FILE* file;
    file = fopen(argv[1], "r");
    if (file == NULL) 
	{
		printf("Error While opening file");
		exit(1);
	}
	keypad(win, TRUE);
	scrollok (win, TRUE);
	
    bool end = false;
    int c, i = 0;
    while(!end){
    	PrintText(win, file, i);
    	while(c = wgetch(win)){
    		if(c == 27) {
    			end = true;
    			break;
    		} else if(c == 32){
    			if(!feof(file)){
    				werase(win);
    			}
    			break;	
    		}
    	}
    	i++;
    }
    fclose(file);
	endwin();
}
