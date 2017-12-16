
#ifndef ARDUINO

#include "cursesRenderer.h"
#include "game.h"

int main(){
    startRenderer(update); // update is in game.h
    return 0;
}

#endif
