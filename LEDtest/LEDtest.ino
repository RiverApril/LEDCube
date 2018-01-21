
const int columnBluePins[4][4] = { {5, 48, 46, 44}, {42, 40, 38, 36}, {34, 32, 30, 28}, {1, 2, 22, 52} };
const int columnRedPins[4][4] = { {6, 31, 39, 47}, {0, 33, 41, 49}, {25, 35, 3, 4}, {23, 37, 45, 53} };

const int levelPins[4] = { 8, 9, 10, 11};



void setup() {
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
}

void loop() {
  for(int z = 0; z < 4; z++){
    digitalWrite(levelPins[z], HIGH);
    for(int x = 0; x < 4; x++){
      for(int y = 0; y < 4; y++){
        digitalWrite(columnRedPins[x][y], HIGH);
        delay(2000);
        digitalWrite(columnRedPins[x][y], LOW);
        digitalWrite(columnBluePins[x][y], HIGH);
        delay(2000);
        digitalWrite(columnBluePins[x][y], LOW);
      }
    }
    digitalWrite(levelPins[z], LOW);
  }
}
