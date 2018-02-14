
#define TEXT_SPEED 6
#define SCROLL_SPEED 3


void initGame(){

}

void update(){


    for(int c=1;c<=2;c++){
        for(int i=0;i<2;i++){
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    display.set(i, j, k, c);
                    display.set(i+2, j, k, c);
                }
            }
            delay(1000/FPS);
            for(int j=0;j<4;j++){
                for(int k=0;k<4;k++){
                    display.set(i, j, k, 0);
                    display.set(i+2, j, k, 0);
                }
            }
        }
    }

}
