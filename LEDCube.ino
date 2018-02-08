
#include "chipKitRenderer.h"
#include "game.h"

void setup(){
  startRenderer(initGame);
}

void loop(){
  gameLoop(update);
}

