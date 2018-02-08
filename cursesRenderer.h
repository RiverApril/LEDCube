#include <ncurses.h>
#include "cube.h"

#define KEY_Xd 0
#define KEY_Xu 1
#define KEY_Yd 2
#define KEY_Yu 3
#define KEY_Zd 4
#define KEY_Zu 5
#define KEY_Enter 6
#define KEY_Exit 7
#define KEY_COUNT 8

bool inputs[KEY_COUNT];

Cube display;

void startRenderer( void(*initGame)(), void(*update)(bool*, bool*) ){

    initscr();
    noecho();
    
    start_color();
    init_pair(0, COLOR_WHITE+8, COLOR_BLACK);
    init_pair(1, COLOR_WHITE+8, COLOR_RED+8);
    init_pair(2, COLOR_WHITE+8, COLOR_BLUE+8);
    init_pair(3, COLOR_WHITE+8, COLOR_MAGENTA+8);
    timeout(100);

    initGame();
    
    while(true){

        for(int i = 0; i < KEY_COUNT; i++){
            inputs[i] = false;
        }

        char in = getch();
        switch(in){
            case 'a': inputs[KEY_Xd] = true; break;
            case 'd': inputs[KEY_Xu] = true; break;
            case 's': inputs[KEY_Yd] = true; break;
            case 'w': inputs[KEY_Yu] = true; break;
            case 'q': inputs[KEY_Zd] = true; break;
            case 'e': inputs[KEY_Zu] = true; break;
            case ' ': inputs[KEY_Enter] = true; break;
            case 27: inputs[KEY_Exit] = true; break;
        }

        update(inputs, inputs);

        for(unsigned char y = 0; y < 4; y++){
            for(unsigned char z = 0; z < 4; z++){
                for(unsigned char x = 0; x < 4; x++){
                    attron(COLOR_PAIR(display.get(x, y, z)));
                    mvaddch((4-1-y)*2, z*14+x*3, '.');
                    attroff(COLOR_PAIR(display.get(x, y, z)));
                }
            }
        }
        mvprintw(4*2+0, 0, "d: x+");
        mvprintw(4*2+1, 0, "a: x-");
        mvprintw(4*2+2, 0, "w: y+");
        mvprintw(4*2+3, 0, "s: y-");
        mvprintw(4*2+4, 0, "e: z+");
        mvprintw(4*2+5, 0, "q: z-");
        mvprintw(4*2+6, 0, "space: enter");
        mvprintw(4*2+7, 0, "escape: exit");
    }

}