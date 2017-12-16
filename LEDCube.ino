
#include "chipKitRenderer.h"
#include "game.h"

void setup(){
  startRenderer();
}

void loop(){
  gameLoop(update);
}

