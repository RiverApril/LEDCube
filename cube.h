
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

    void set2DTrans(unsigned char x, unsigned char y, unsigned char c){
        // for now just always on top z in top left corner
        set(x, y, 3, c);
    }

    void set2DPattern(unsigned char y, const char* pat, unsigned char c){
        for(unsigned char i = 0; i < 4; i++){
            if(pat[i] == '\0'){ break; }
            if(pat[i] != ' '){
                set2DTrans(i, y, c);
            }
        }
    }

    void letter(char l, unsigned char c){
        switch(l){
            // Just letters I need for now
            case '!':{
                set2DPattern(3, " #  ", c);
                set2DPattern(2, " #  ", c);
                set2DPattern(1, "    ", c);
                set2DPattern(0, " #  ", c);
                break;
            }
            case '1':{
                set2DPattern(3, " #  ", c);
                set2DPattern(2, "##  ", c);
                set2DPattern(1, " #  ", c);
                set2DPattern(0, "### ", c);
                break;
            }
            case '2':{
                set2DPattern(3, "####", c);
                set2DPattern(2, "  ##", c);
                set2DPattern(1, "##  ", c);
                set2DPattern(0, "####", c);
                break;
            }
            case '4':{
                set2DPattern(3, "#  #", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "####", c);
                set2DPattern(0, "   #", c);
                break;
            }
            case 'A':{
                set2DPattern(3, " ## ", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "####", c);
                set2DPattern(0, "#  #", c);
                break;
            }
            case 'B':{
                set2DPattern(3, "##  ", c);
                set2DPattern(2, "# # ", c);
                set2DPattern(1, "## #", c);
                set2DPattern(0, "### ", c);
                break;
            }
            case 'C':{
                set2DPattern(3, "####", c);
                set2DPattern(2, "#   ", c);
                set2DPattern(1, "#   ", c);
                set2DPattern(0, "####", c);
                break;
            }
            case 'E':{
                set2DPattern(3, "####", c);
                set2DPattern(2, "##  ", c);
                set2DPattern(1, "#   ", c);
                set2DPattern(0, "####", c);
                break;
            }
            case 'H':{
                set2DPattern(3, "#  #", c);
                set2DPattern(2, "####", c);
                set2DPattern(1, "#  #", c);
                set2DPattern(0, "#  #", c);
                break;
            }
            case 'I':{
                set2DPattern(3, "###", c);
                set2DPattern(2, " # ", c);
                set2DPattern(1, " # ", c);
                set2DPattern(0, "###", c);
                break;
            }
            case 'L':{
                set2DPattern(3, "#  ", c);
                set2DPattern(2, "#  ", c);
                set2DPattern(1, "#  ", c);
                set2DPattern(0, "###", c);
                break;
            }
            case 'N':{
                set2DPattern(3, "#  #", c);
                set2DPattern(2, "## #", c);
                set2DPattern(1, "# ##", c);
                set2DPattern(0, "#  #", c);
                break;
            }
            case 'O':{
                set2DPattern(3, " ## ", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "#  #", c);
                set2DPattern(0, " ## ", c);
                break;
            }
            case 'P':{
                set2DPattern(3, "### ", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "### ", c);
                set2DPattern(0, "#   ", c);
                break;
            }
            case 'S':{
                set2DPattern(3, "####", c);
                set2DPattern(2, "##  ", c);
                set2DPattern(1, "  ##", c);
                set2DPattern(0, "####", c);
                break;
            }
            case 'T':{
                set2DPattern(3, "###", c);
                set2DPattern(2, " # ", c);
                set2DPattern(1, " # ", c);
                set2DPattern(0, " # ", c);
                break;
            }
            case 'U':{
                set2DPattern(3, "#  #", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "#  #", c);
                set2DPattern(0, "####", c);
                break;
            }
            case 'W':{
                set2DPattern(3, "#  #", c);
                set2DPattern(2, "#  #", c);
                set2DPattern(1, "# ##", c);
                set2DPattern(0, "####", c);
                break;
            }
        }
    }

};
