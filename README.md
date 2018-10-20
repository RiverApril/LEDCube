# LED Cube Games

This is code for a small 4x4x4 bi-colored LED cube to run some little games.

Games include:
- Tic-Tac-Toe 4 in a row *in 3D!*
- Connect 4 *in 3D!*
- Battleship *in space!*
- Reversi *in 3D!*

It is designed to run on the chipKIT Max32 microcontroller programmed using the Arduino IDE.

There is a ncurses version that runs in the terminal that can be used for testing as well.
For this version the key mappings are:
- D: Right (x up)
- A: Left (x down)
- W: In (y up)
- S: Out (y down)
- E: Up (z up)
- Q: Down (z down)
- Spacebar: Enter
- Escape: Exit

# Games

The program starts in a menu showing the logo of the first game: Tic-Tac-Toe.
After a small delay the logo will disappear and the words "TICTACTOE" will show up on the top layer one letter at a time.
The buttons (pins listed near the top of [chipKitRenderer.h](chipKitRenderer.h)) Xd (X down) and Xu (X up) can be used to cycle through the games.

In the menu each game is displayed in a similar manner as Tic-Tac-Toe with first the logo appearing then the name scrolling by.
To play a game press the Enter button.

Each game plays similarly, there is a cursor (in the form of a blinking LED) that can be moved around with the directional keys.
To conform a move the enter key should be pressed.

# Hardware Design

The Cube is setup to have 32 columns (16 columns really but 2 wires in each for the 2 colors) and 4 layers.
When a column is powered and a layer is powered the corresponding LED will light.
Each light is a bi-colored LED with blue and red individually wired to their own column.

Wiring diagram:
~~~~                           4 LEDs
                            +----|>----...
                            |
                            +----|>----... Each is connected to one of 4 transistors
                            |
                  Small     +----|>----...
                 Resistor   |
COLUMN PIN -----'\/\/\/\,---+----|>------+
(32 in total)                            |
                          Big           /
                        Resistor      |/
LAYER PIN --------------'\/\/\/\,-----|   NPN Transistor
(4 in total)                          |\
                                       _\'
                                         |
                                       GROUND
               
                      Big
                    Resistor
Voltage Source -----'\/\/\/\,---+----------- BUTTON PIN
                                |            (8 in total)
                                |
                                |      /
                                +-----' -------- GROUND
                                    Button
~~~~

There are 8 buttons total: 6 directional buttons, 2 for each dimension, and 2 buttons for enter and exit.

The button layout that was used is similar to a gamepad with the 4 planar directional buttons on the left and the two up/down buttons on the right with enter and exit in the middle.

The column, layer, and input pins used are listed in arrays in the [chipKitRenderer.h](chipKitRenderer.h) file. (but they can be (almost) any pins) 



