
#define OFF 0
#define RED 1
#define BLUE 2
#define MAGENTA 3

class Cube{
private:
    unsigned char matrix[4][4][4];

public:
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
                set2DPattern(3, "####", c, z);
                set2DPattern(2, "  ##", c, z);
                set2DPattern(1, "##  ", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
            case '4':{
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "####", c, z);
                set2DPattern(0, "   #", c, z);
                break;
            }
            case 'A':{
                set2DPattern(3, " ## ", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "####", c, z);
                set2DPattern(0, "#  #", c, z);
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
                set2DPattern(3, "####", c, z);
                set2DPattern(2, "#   ", c, z);
                set2DPattern(1, "#   ", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
            case 'D':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, "### ", c, z);
                break;
            }
            case 'E':{
                set2DPattern(3, "####", c, z);
                set2DPattern(2, "##  ", c, z);
                set2DPattern(1, "#   ", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
            case 'G':{
                set2DPattern(3, "####", c, z);
                set2DPattern(2, "#   ", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
            case 'H':{
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "####", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, "#  #", c, z);
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
                set2DPattern(0, "####", c, z);
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
                set2DPattern(3, " ## ", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, " ## ", c, z);
                break;
            }
            case 'P':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "### ", c, z);
                set2DPattern(0, "#   ", c, z);
                break;
            }
            case 'R':{
                set2DPattern(3, "### ", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "### ", c, z);
                set2DPattern(0, "#  #", c, z);
                break;
            }
            case 'S':{
                set2DPattern(3, "####", c, z);
                set2DPattern(2, "##  ", c, z);
                set2DPattern(1, "  ##", c, z);
                set2DPattern(0, "####", c, z);
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
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, "####", c, z);
                break;
            }
            case 'V':{
                set2DPattern(3, "#  #", c, z);
                set2DPattern(2, "#  #", c, z);
                set2DPattern(1, "#  #", c, z);
                set2DPattern(0, " ## ", c, z);
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
