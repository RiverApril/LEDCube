
#ifndef ARDUINO

#include "cursesRenderer.h"
#include "game.h"

int main(){
    startRenderer(initGame, update);
    return 0;
}

#endif
