
#include "cube.h"

#define TICKS_PER_SECOND 80000000
 
#define T3_ON 0x8000
#define T3_PS_1_1 0
#define T3_SOURCE_INT 0


#define FPS 1

/* Chipkit Max32 pin weirdness:
 *  
 * Pins 24, 26, 27 are not able to output voltage
 * 
 * 43 & 51 are connected to each other
 * 29 & 50 are connected to each other
 * After some research, other connected pairs found: 
 * 40 & 65
 * 41 & 66
 * 42 & 67
 * 
 */

const int columnBluePins[4][4] = { {44, 46, 48, 5}, {36, 38, 40, 42}, {28, 30, 32, 34}, {52, 22, 2, 1} };
const int columnRedPins[4][4] = { {47, 39, 31, 6}, {49, 41, 33, 0}, {4, 3, 35, 25}, {53, 45, 37, 23} };

const int levelPins[4] = { 8, 9, 10, 11};

int current_level = 0;

Cube display;

void __attribute__((interrupt)) myISR(){ // Timer 3
  
  digitalWrite(levelPins[(current_level+3)%4], LOW);
  for(int x = 0; x < 4; x++){
    for(int y = 0; y < 4; y++){
      digitalWrite(columnRedPins[x][y], display.get(x, y, current_level)&1?HIGH:LOW);
      digitalWrite(columnBluePins[x][y], display.get(x, y, current_level)&2?HIGH:LOW);
    }
  }
  digitalWrite(levelPins[current_level], HIGH);
  
  if(current_level >= 3){
    current_level = 0;
  }else{
    current_level++;
  }

  clearIntFlag(_TIMER_3_IRQ);
  
}

void start_timer_3(uint32_t frequency) {
  uint32_t period;  
  period = TICKS_PER_SECOND / frequency;
  T3CONCLR = T3_ON;         // Turn the timer off
  T3CON = T3_PS_1_1;        // Set the prescaler
  TMR3 = 0;                 // Clear the counter
  PR3 = period;             // Set the period
  T3CONSET = T3_ON;         // Turn the timer on
  setIntVector(_TIMER_3_VECTOR, myISR);
  setIntPriority(_TIMER_3_VECTOR, 4, 0);
  clearIntFlag(_TIMER_3_IRQ);
  setIntEnable(_TIMER_3_IRQ);
} 

void gameLoop( void(*update)() ) {
  update();
}

void startRenderer( void(*initGame)() ){
  for(int x = 0; x < 4; x++){
    for(int y = 0; y < 4; y++){
      pinMode(columnRedPins[x][y], OUTPUT);
      pinMode(columnBluePins[x][y], OUTPUT);
      digitalWrite(columnRedPins[x][y], LOW);
      digitalWrite(columnBluePins[x][y], LOW);
    }
  }
  for(int z = 0; z < 4; z++){
    pinMode(levelPins[z], OUTPUT);
    digitalWrite(levelPins[z], LOW);
  }

  initGame();

  start_timer_3(8000);
  
}
