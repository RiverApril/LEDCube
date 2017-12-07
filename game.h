
#ifdef USE_CURSES
#include "renderer.h"
#else
// use arduino renderer (once it's made)
#endif

#define GAME_MENU 0
#define GAME_TTT 1
#define GAME_CONNECT4 2
#define GAME_BATTLESHIP 3

#define GAME_COUNT 4

int tick = 0;
int game = GAME_MENU;
bool needsReset = false;
Cube utilCube1;
Cube utilCube2;

namespace CursorSpace{
    char cursorX = 0;
    char cursorY = 0;
    char cursorZ = 0;
}

namespace MenuSpace{

    int select = 0;
    const int selectCount = GAME_COUNT-1;

    void play(bool inputs[]){

        if(inputs[KEY_Xd]){
            select--;
            tick = 0;
        }
        if(inputs[KEY_Xu]){ 
            select++;
            tick = 0;
        }

        while(select < 0){ select += selectCount; }
        while(select >= selectCount){ select -= selectCount; }

        display.clearAll();

        const int logoTime = 40; // 4 seconds

        switch(select+1){
            case GAME_TTT:{
                if(tick < logoTime){
                    display.set2DPattern(3, "# # ", 1);
                    display.set2DPattern(2, " #  ", 1);
                    display.set2DPattern(1, "# # ", 1);
                    
                    display.set2DPattern(2, "  # ", 2);
                    display.set2DPattern(1, " # #", 2);
                    display.set2DPattern(0, "  # ", 2);
                }else{
                    switch(((tick-logoTime)/4)%10){
                        case 0: display.letter('T', 1); break;
                        case 1: display.letter('I', 1); break;
                        case 2: display.letter('C', 1); break;
                        case 3: display.letter('T', 2); break;
                        case 4: display.letter('A', 2); break;
                        case 5: display.letter('C', 2); break;
                        case 6: display.letter('T', 3); break;
                        case 7: display.letter('O', 3); break;
                        case 8: display.letter('E', 3); break;
                        case 9: break;
                    }
                }

                break;
            }
            case GAME_CONNECT4:{
                if(tick < logoTime){
                    display.set2DPattern(3, "### ", 1);
                    display.set2DPattern(2, "#   ", 1);
                    display.set2DPattern(1, "#   ", 1);
                    display.set2DPattern(0, "### ", 1);
                    
                    display.set2DPattern(2, " # #", 2);
                    display.set2DPattern(1, " ###", 2);
                    display.set2DPattern(0, "   #", 2);
                }else{
                    switch(((tick-logoTime)/4)%9){
                        case 0: display.letter('C', 2); break;
                        case 1: display.letter('O', 2); break;
                        case 2: display.letter('N', 2); break;
                        case 3: display.letter('N', 1); break;
                        case 4: display.letter('E', 1); break;
                        case 5: display.letter('C', 1); break;
                        case 6: display.letter('T', 1); break;
                        case 7: display.letter('4', 3); break;
                        case 8: break;
                    }
                }

                break;
            }
            case GAME_BATTLESHIP:{

                if(tick < logoTime){
                    display.set2DPattern(3, "  # ", 3);
                    display.set2DPattern(2, " #  ", 1);
                    display.set2DPattern(1, "####", 1);
                    display.set2DPattern(0, "####", 2);
                }else{
                    switch(((tick-logoTime)/4)%11){
                        case 0: display.letter('B', 1); break;
                        case 1: display.letter('A', 1); break;
                        case 2: display.letter('T', 1); break;
                        case 3: display.letter('T', 1); break;
                        case 4: display.letter('L', 1); break;
                        case 5: display.letter('E', 1); break;
                        case 6: display.letter('S', 2); break;
                        case 7: display.letter('H', 2); break;
                        case 8: display.letter('I', 2); break;
                        case 9: display.letter('P', 2); break;
                        case 10: break;
                    }
                }

                break;
            }
        }

        if(inputs[KEY_Enter]){
            tick = 0;
            needsReset = true;
            CursorSpace::cursorX = 0;
            CursorSpace::cursorY = 0;
            CursorSpace::cursorZ = 0;
            game = select+1;
        }
    }
}

void checkWin(Cube& ticTacToe, Cube& winCube, unsigned char& winner){
    // check in z
    for(unsigned char x = 0; !winner && x < 4; x++){
        for(unsigned char y = 0; !winner && y < 4; y++){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(x, y, 0);
            if(a != 0){
                winCube.set(x, y, 0, a);
                for(unsigned char z = 1; z < 4; z++){
                    if(ticTacToe.get(x, y, z) != a){
                        a = 0;
                        break;
                    }else{
                        winCube.set(x, y, z, a);
                    }
                }
                if(a != 0){
                    winner = a;
                }
            }
        }
    }
    // check in y
    for(unsigned char x = 0; !winner && x < 4; x++){
        for(unsigned char z = 0; !winner && z < 4; z++){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(x, 0, z);
            if(a != 0){
                winCube.set(x, 0, z, a);
                for(unsigned char y = 1; y < 4; y++){
                    if(ticTacToe.get(x, y, z) != a){
                        a = 0;
                        break;
                    }else{
                        winCube.set(x, y, z, a);
                    }
                }
                if(a != 0){
                    winner = a;
                }
            }
        }
    }
    // check in x
    for(unsigned char y = 0; !winner && y < 4; y++){
        for(unsigned char z = 0; !winner && z < 4; z++){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(0, y, z);
            if(a != 0){
                winCube.set(0, y, z, a);
                for(unsigned char x = 1; x < 4; x++){
                    if(ticTacToe.get(x, y, z) != a){
                        a = 0;
                        break;
                    }else{
                        winCube.set(x, y, z, a);
                    }
                }
                if(a != 0){
                    winner = a;
                }
            }
        }
    }
    // check in yz
    for(unsigned char x = 0; !winner && x < 4; x++){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(x, 0, 0);
        winCube.set(x, 0, 0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(x, i, i)){
                a = 0;
            }else{
                winCube.set(x, i, i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
        if(!winner){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(x, 3-0, 0);
            winCube.set(x, 3-0, 0, a);
            for(int i = 1; i < 4; i++){
                if(a != ticTacToe.get(x, 3-i, i)){
                    a = 0;
                }else{
                    winCube.set(x, 3-i, i, a);
                }
            }
            if(a != 0){
                winner = a;
            }
        }
    }
    // check in xy
    for(unsigned char z = 0; !winner && z < 4; z++){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(0, 0, z);
        winCube.set(0, 0, z, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(i, i, z)){
                a = 0;
            }else{
                winCube.set(i, i, z, a);
            }
        }
        if(a != 0){
            winner = a;
        }
        if(!winner){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(3-0, 0, z);
            winCube.set(3-0, 0, z, a);
            for(int i = 1; i < 4; i++){
                if(a != ticTacToe.get(3-i, i, z)){
                    a = 0;
                }else{
                    winCube.set(3-i, i, z, a);
                }
            }
            if(a != 0){
                winner = a;
            }
        }
    }
    // check in xz
    for(unsigned char y = 0; !winner && y < 4; y++){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(0, y, 0);
        winCube.set(0, y, 0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(i, y, i)){
                a = 0;
            }else{
                winCube.set(i, y, i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
        if(!winner){
            winCube.clearAll();
            unsigned char a = ticTacToe.get(3-0, y, 0);
            winCube.set(3-0, y, 0, a);
            for(int i = 1; i < 4; i++){
                if(a != ticTacToe.get(3-i, y, i)){
                    a = 0;
                }else{
                    winCube.set(3-i, y, i, a);
                }
            }
            if(a != 0){
                winner = a;
            }
        }
    }
    // check in xyz
    if(!winner){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(0, 0, 0);
        winCube.set(0, 0, 0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(i, i, i)){
                a = 0;
            }else{
                winCube.set(i, i, i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
    }
    if(!winner){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(3-0, 0, 0);
        winCube.set(3-0, 0, 0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(3-i, i, i)){
                a = 0;
            }else{
                winCube.set(3-i, i, i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
    }
    if(!winner){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(0, 3-0, 0);
        winCube.set(0, 3-0, 0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(i, 3-i, i)){
                a = 0;
            }else{
                winCube.set(i, 3-i, i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
    }
    if(!winner){
        winCube.clearAll();
        unsigned char a = ticTacToe.get(0, 0, 3-0);
        winCube.set(0, 0, 3-0, a);
        for(int i = 1; i < 4; i++){
            if(a != ticTacToe.get(i, i, 3-i)){
                a = 0;
            }else{
                winCube.set(i, i, 3-i, a);
            }
        }
        if(a != 0){
            winner = a;
        }
    }
}

namespace TTTSpace{
    using namespace CursorSpace;

    Cube& ticTacToe = utilCube1;
    Cube& winCube = utilCube2;
    bool player1Turn = true;
    unsigned char winner = 0;

    void play(bool inputs[]){

        if(needsReset){
            ticTacToe.clearAll();
            winCube.clearAll();
            player1Turn = true;
            winner = 0;

            needsReset = false;
        }

        display.clearAll();

        if(winner){

            for(unsigned char x = 0; x < 4; x++){
                for(unsigned char y = 0; y < 4; y++){
                    for(unsigned char z = 0; z < 4; z++){
                        unsigned char w = winCube.get(x, y, z);
                        if(w != 0){
                            if(tick%8<4){
                                display.set(x, y, z, w);
                            }
                        }else{
                            display.set(x, y, z, ticTacToe.get(x, y, z));
                        }
                    }
                }
            }
            
            if(inputs[KEY_Enter]){
                game = GAME_MENU;
            }
            
        }else{

            for(unsigned char x = 0; x < 4; x++){
                for(unsigned char y = 0; y < 4; y++){
                    for(unsigned char z = 0; z < 4; z++){
                        display.set(x, y, z, ticTacToe.get(x, y, z));
                    }
                }
            }

            if(tick%4 < 2){
                unsigned char ttt = ticTacToe.get(cursorX, cursorY, cursorZ);
                display.set(cursorX, cursorY, cursorZ, ttt==0?(player1Turn?1:2):3);
            }

            if(inputs[KEY_Enter]){
                if(ticTacToe.get(cursorX, cursorY, cursorZ) == 0){
                    ticTacToe.set(cursorX, cursorY, cursorZ, player1Turn?1:2);
                    player1Turn = !player1Turn;
                    checkWin(ticTacToe, winCube, winner);
                }
            }

        }

        
    }
}

namespace CONNECT4Space{
    using namespace CursorSpace;

    Cube& sandCube = utilCube1;
    Cube& winCube = utilCube2;
    bool player1Turn = true;
    unsigned char winner = 0;

    void play(bool inputs[]){

        if(needsReset){
            sandCube.clearAll();
            winCube.clearAll();
            player1Turn = true;
            winner = 0;

            needsReset = false;
        }

        display.clearAll();

        if(winner){

            for(unsigned char x = 0; x < 4; x++){
                for(unsigned char y = 0; y < 4; y++){
                    for(unsigned char z = 0; z < 4; z++){
                        unsigned char w = winCube.get(x, y, z);
                        if(w != 0){
                            if(tick%8<4){
                                display.set(x, y, z, w);
                            }
                        }else{
                            display.set(x, y, z, sandCube.get(x, y, z));
                        }
                    }
                }
            }
            
            if(inputs[KEY_Enter]){
                game = GAME_MENU;
            }
            
        }else{

            for(unsigned char x = 0; x < 4; x++){
                for(unsigned char y = 0; y < 4; y++){
                    for(unsigned char z = 0; z < 4; z++){
                        display.set(x, y, z, sandCube.get(x, y, z));
                    }
                }
            }

            if(tick%4 < 2){
                unsigned char ttt = sandCube.get(cursorX, cursorY, 3);
                display.set(cursorX, cursorY, 3, ttt==0?(player1Turn?1:2):3);
            }

            if(inputs[KEY_Enter]){
                if(sandCube.get(cursorX, cursorY, 3) == 0){
                    char z;
                    for(z = 2; z >= 0; z--){
                        if(sandCube.get(cursorX, cursorY, z) != 0){
                            break;
                        }
                    }
                    z++;
                    sandCube.set(cursorX, cursorY, z, player1Turn?1:2);
                    player1Turn = !player1Turn;
                    checkWin(sandCube, winCube, winner);
                }
            }

        }

        
    }
}

namespace BATTLESHIPSpace{

    Cube& p1Field = utilCube1;
    Cube& p2Field = utilCube2;
    const int modeChoosePre = 0;
    const int modeChoosePos = 1;
    const int modeChooseAngle = 2;

    const int modeReadyForPlayer = 3;
    const int modeOwnFiled = 4;
    const int modeViewOfOtherBefore = 5;
    const int modeViewOfOtherAfter = 6;

    const int modeWinner = 7;
    const int modeShowFieldEnd = 8;

    int winner = 0;
    int mode = modeChoosePre;
    int editShipIndex = 0;
    bool player1Turn = true;
    char shipPlaceX = 0;
    char shipPlaceY = 0;
    char shipPlaceZ = 0;
    char shipPlaceAX = 0;
    char shipPlaceAY = 0;
    char shipPlaceAZ = 0;

    const unsigned char shipCount = 4;
    const unsigned char shipSizes[shipCount] = {3, 3, 3, 2};

    void play(bool inputs[]){
        using namespace CursorSpace;

        if(needsReset){
            p1Field.clearAll();
            p2Field.clearAll();
            winner = 0;
            mode = modeChoosePre;
            editShipIndex = 0;
            player1Turn = true;
            shipPlaceX = 0;
            shipPlaceY = 0;
            shipPlaceZ = 0;
            shipPlaceAX = 0;
            shipPlaceAY = 0;
            shipPlaceAZ = 0;
            needsReset = false;
        }

        display.clearAll();

        switch(mode){
            case modeChoosePre:{
                switch((tick/4)%8){
                    case 0: display.letter('P', 1); break;
                    case 1: display.letter(player1Turn?'1':'2', 1); break;
                    case 2: display.letter('S', 2); break;
                    case 3: display.letter('E', 2); break;
                    case 4: display.letter('T', 2); break;
                    case 5: display.letter('U', 2); break;
                    case 6: display.letter('P', 2); break;
                    case 7: break;
                }
                if(inputs[KEY_Enter]){
                    mode = modeChoosePos;
                }
                break;
            }
            case modeChoosePos:{
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            display.set(x, y, z, (player1Turn?p1Field:p2Field).get(x, y, z));
                        }
                    }
                }
                if(tick%4 < 2){
                    unsigned char ttt = (player1Turn?p1Field:p2Field).get(cursorX, cursorY, cursorZ);
                    display.set(cursorX, cursorY, cursorZ, 1);
                }
                if(inputs[KEY_Enter]){
                    if((player1Turn?p1Field:p2Field).get(cursorX, cursorY, cursorZ) == 0){
                        shipPlaceX = cursorX;
                        shipPlaceY = cursorY;
                        shipPlaceZ = cursorZ;
                        mode = modeChooseAngle;
                    }
                }
                break;
            }
            case modeChooseAngle:{
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            display.set(x, y, z, (player1Turn?p1Field:p2Field).get(x, y, z));
                        }
                    }
                }
                if(inputs[KEY_Xd]){ shipPlaceAX = -1; shipPlaceAY = 0; shipPlaceAZ = 0; }
                if(inputs[KEY_Xu]){ shipPlaceAX = 1; shipPlaceAY = 0; shipPlaceAZ = 0; }
                if(inputs[KEY_Yd]){ shipPlaceAY = -1; shipPlaceAX = 0; shipPlaceAZ = 0; }
                if(inputs[KEY_Yu]){ shipPlaceAY = 1; shipPlaceAX = 0; shipPlaceAZ = 0; }
                if(inputs[KEY_Zd]){ shipPlaceAZ = -1; shipPlaceAY = 0; shipPlaceAX = 0; }
                if(inputs[KEY_Zu]){ shipPlaceAZ = 1; shipPlaceAY = 0; shipPlaceAX = 0; }
                bool good = shipPlaceAX || shipPlaceAY || shipPlaceAZ;
                for(char i = 0; i < shipSizes[editShipIndex]; i++){
                    char x = shipPlaceX + shipPlaceAX*i;
                    char y = shipPlaceY + shipPlaceAY*i;
                    char z = shipPlaceZ + shipPlaceAZ*i;
                    if(x >= 0 && x < 4 && y >= 0 && y < 4 && z >= 0 && z < 4 && (player1Turn?p1Field:p2Field).get(x, y, z) == 0){
                        display.set(x, y, z, 1);
                    }else{
                        good = false;
                    }
                }
                if(good){
                    if(inputs[KEY_Enter]){
                        for(char i = 0; i < shipSizes[editShipIndex]; i++){
                            char x = shipPlaceX + shipPlaceAX*i;
                            char y = shipPlaceY + shipPlaceAY*i;
                            char z = shipPlaceZ + shipPlaceAZ*i;
                            (player1Turn?p1Field:p2Field).set(x, y, z, 3);
                        }
                        editShipIndex++;
                        if(editShipIndex == shipCount){
                            if(player1Turn){
                                player1Turn = false;
                                editShipIndex = 0;
                                mode = modeChoosePre;
                            }else{
                                player1Turn = true;
                                mode = modeReadyForPlayer;
                            }
                        }else{
                            mode = modeChoosePos;
                        }
                    }
                }
                break;
            }
            case modeReadyForPlayer:{
                switch((tick/4)%2){
                    case 0: display.letter('P', 1); break;
                    case 1: display.letter(player1Turn?'1':'2', 1); break;
                }
                if(inputs[KEY_Enter]){
                    mode = modeOwnFiled;
                }
                break;
            }
            case modeOwnFiled:{
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            display.set(x, y, z, (player1Turn?p1Field:p2Field).get(x, y, z));
                        }
                    }
                }
                if(inputs[KEY_Enter]){
                    mode = modeViewOfOtherBefore;
                }
                break;
            }
            case modeViewOfOtherBefore:{
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            unsigned char p = (player1Turn?p2Field:p1Field).get(x, y, z);
                            if(p != 3){
                                display.set(x, y, z, p);
                            }
                        }
                    }
                }
                if(tick%4 < 2){
                    unsigned char ttt = (player1Turn?p2Field:p1Field).get(cursorX, cursorY, cursorZ);
                    display.set(cursorX, cursorY, cursorZ, (ttt==1||ttt==2)?1:2);
                }
                if(inputs[KEY_Enter]){
                    unsigned char ttt = (player1Turn?p2Field:p1Field).get(cursorX, cursorY, cursorZ);
                    if(ttt == 0 || ttt == 3){
                        (player1Turn?p2Field:p1Field).set(cursorX, cursorY, cursorZ, ttt==0?2:1);
                        mode = modeViewOfOtherAfter;
                    }
                }
                break;
            }
            case modeViewOfOtherAfter:{
                bool playerWon = true;
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            unsigned char p = (player1Turn?p2Field:p1Field).get(x, y, z);
                            if(p != 3){
                                display.set(x, y, z, p);
                            }else{
                                playerWon = false;
                            }
                        }
                    }
                }
                if(inputs[KEY_Enter]){
                    if(playerWon){
                        mode = modeWinner;
                        winner = player1Turn?1:2;
                    }else{
                        mode = modeReadyForPlayer;
                        player1Turn = !player1Turn;
                    }
                }
                break;
            }
            case modeWinner:{
                switch((tick/4)%8){
                    case 0: display.letter('P', 1); break;
                    case 1: display.letter(player1Turn?'1':'2', 1); break;
                    case 2: display.letter('W', 2); break;
                    case 3: display.letter('I', 2); break;
                    case 4: display.letter('N', 2); break;
                    case 5: display.letter('S', 2); break;
                    case 6: display.letter('!', 2); break;
                    case 7: break;
                }
                if(inputs[KEY_Enter]){
                    mode = modeShowFieldEnd;
                    player1Turn = true;
                }
                break;
            }
            case modeShowFieldEnd:{
                for(unsigned char x = 0; x < 4; x++){
                    for(unsigned char y = 0; y < 4; y++){
                        for(unsigned char z = 0; z < 4; z++){
                            display.set(x, y, z, (player1Turn?p1Field:p2Field).get(x, y, z));
                        }
                    }
                }
                if(inputs[KEY_Enter]){
                    player1Turn = !player1Turn;
                }
            }
        }

    }

}

void update(bool inputs[]){

    tick++;

    {
        using namespace CursorSpace;
        if(inputs[KEY_Xd]){ cursorX--; }
        if(inputs[KEY_Xu]){ cursorX++; }
        if(inputs[KEY_Yd]){ cursorY--; }
        if(inputs[KEY_Yu]){ cursorY++; }
        if(inputs[KEY_Zd]){ cursorZ--; }
        if(inputs[KEY_Zu]){ cursorZ++; }

        while(cursorX < 0){ cursorX += 4; }
        while(cursorY < 0){ cursorY += 4; }
        while(cursorZ < 0){ cursorZ += 4; }
        while(cursorX > 3){ cursorX -= 4; }
        while(cursorY > 3){ cursorY -= 4; }
        while(cursorZ > 3){ cursorZ -= 4; }
    }

    switch(game){
        case GAME_MENU:{
            MenuSpace::play(inputs);
            break;
        }
        case GAME_TTT:{
            TTTSpace::play(inputs);
            break;
        }
        case GAME_CONNECT4:{
            CONNECT4Space::play(inputs);
            break;
        }
        case GAME_BATTLESHIP:{
            BATTLESHIPSpace::play(inputs);
            break;
        }
    }

    if(inputs[KEY_Exit]){
        game = GAME_MENU;
    }

}