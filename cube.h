
#define OFF 0
#define RED 1
#define BLUE 2
#define MAGENTA 3

#include "letterCodes.h"

struct CodedString{

    unsigned short* data;
    unsigned long length;

    CodedString(){}

    CodedString(unsigned long length){
        this->length = length;
        data = new unsigned short[length];
    }
};

class Cube{
private:
    unsigned char matrix[4][4][4];

public:

    static CodedString makeCodedString(const char* s){
        int ci = 0;
        int length = 0;
        for(int i = 0; s[i] != '\0'; i++){
            unsigned short last = (letterCodes[s[i]]&0x000F) >> 0;
            length += last==0?4:5;
        }
        CodedString coded(length);
        for(int i = 0; s[i] != '\0'; i++){
            unsigned short last = (letterCodes[s[i]]&0x000F) >> 0;
            if(last != 0){ // some letters are 3 wide
                coded.data[ci++] = last;
            }
            coded.data[ci++] = ((letterCodes[s[i]]&0x00F0) >> 4);
            coded.data[ci++] = ((letterCodes[s[i]]&0x0F00) >> 8);
            coded.data[ci++] = ((letterCodes[s[i]]&0xF000) >> 12);
            coded.data[ci++] = 0;
        }
        return coded;
    }

    Cube(){
        clearAll();
    }

    void clearAll(){
        for(unsigned char x = 0; x < 4; x++){
            for(unsigned char y = 0; y < 4; y++){
                for(unsigned char z = 0; z < 4; z++){
                    matrix[x][y][z] = OFF;
                }
            }
        }
    }

    void set(unsigned char x, unsigned char y, unsigned char z, unsigned char color){
        matrix[x][y][z] = color;
    }

    unsigned char get(unsigned char x, unsigned char y, unsigned char z){
        return matrix[x][y][z];
    }

    void set2DPattern(unsigned char y, const char* pat, unsigned char c, unsigned char z = 3){
        for(unsigned char i = 0; i < 4; i++){
            if(pat[i] == '\0'){ break; }
            if(pat[i] != ' '){
                set(i, y, z, c);
            }
        }
    }

    void scrollString(CodedString codedString, int tick, unsigned char color){

        const unsigned char xPos[] = {0, 1, 2, 3, 3, 3, 3, 2, 1, 0};
        const unsigned char yPos[] = {0, 0, 0, 0, 1, 2, 3, 3, 3, 3};

        for(int i = 0; i < 10; i++){
            int si = (i-tick)%(codedString.length);
            set(xPos[i], yPos[i], 0, ((codedString.data[si]&1)>>0)?color:0);
            set(xPos[i], yPos[i], 1, ((codedString.data[si]&2)>>1)?color:0);
            set(xPos[i], yPos[i], 2, ((codedString.data[si]&4)>>2)?color:0);
            set(xPos[i], yPos[i], 3, ((codedString.data[si]&8)>>3)?color:0);
        }
    }

    void letter(char l, unsigned char c, unsigned char z = 3){
        switch(l){
            // Just letters I need for now
            case '!':{
                set2DPattern(3, " #  ", c, z);
                set2DPattern(2, " #  ", c, z);
                set2DPattern(1, "    ", c, z);
                set2DPattern(0, " #  ", c, z);
                break;
            }
            case '1':{
                set2DPattern(3, " #  ", c, z);
                set2DPattern(2, "##  ", c, z);
                set2DPattern(1, " #  ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case '2':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, " ## ", c, z);
                set2DPattern(1, "##  ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case '4':{
                set2DPattern(3, "# # ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "### ", c, z);
                set2DPattern(0, "  # ", c, z);
                break;
            }
            case 'A':{
                set2DPattern(3, " #  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "### ", c, z);
                set2DPattern(0, "# # ", c, z);
                break;
            }
            case 'B':{
                set2DPattern(3, "##  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "## #", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'C':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "#   ", c, z);
                set2DPattern(1, "#   ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'D':{
                set2DPattern(3, "##  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, "##  ", c, z);
                break;
            }
            case 'E':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "##  ", c, z);
                set2DPattern(1, "#   ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'G':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "#   ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'H':{
                set2DPattern(3, "# # ", c, z);
                set2DPattern(2, "### ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, "# # ", c, z);
                break;
            }
            case 'I':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, " #  ", c, z);
                set2DPattern(1, " #  ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'L':{
                set2DPattern(3, "#   ", c, z);
                set2DPattern(2, "#   ", c, z);
                set2DPattern(1, "#   ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'N':{
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "## #", c, z);
                set2DPattern(1, "# ##", c, z);
                set2DPattern(0, "#  #", c, z);
                break;
            }
            case 'O':{
                set2DPattern(3, " #  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, " #  ", c, z);
                break;
            }
            case 'P':{
                set2DPattern(3, "##  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "##  ", c, z);
                set2DPattern(0, "#   ", c, z);
                break;
            }
            case 'R':{
                set2DPattern(3, "##  ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "##  ", c, z);
                set2DPattern(0, "# # ", c, z);
                break;
            }
            case 'S':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "##  ", c, z);
                set2DPattern(1, " ## ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'T':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, " #  ", c, z);
                set2DPattern(1, " #  ", c, z);
                set2DPattern(0, " #  ", c, z);
                break;
            }
            case 'U':{
                set2DPattern(3, "# # ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'V':{
                set2DPattern(3, "# # ", c, z);
                set2DPattern(2, "# # ", c, z);
                set2DPattern(1, "# # ", c, z);
                set2DPattern(0, " #  ", c, z);
                break;
            }
            case 'W':{
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "# ##", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
        }
    }

};
