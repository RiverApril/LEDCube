
#ifdef actuallyMakeLetterCodes

#include <stdio.h>

using namespace std;

int main(){

    const char* letters = " !-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const char* letterPixels = 
        "    "
        "    "
        "    "
        "    "

        " #  "
        " #  "
        "    "
        " #  "

        "    "
        "### "
        "    "
        "    "

        "    "
        "    "
        "    "
        " #  "

        "### "
        "# # "
        "# # "
        "### "

        " #  "
        " #  "
        " #  "
        " #  "

        "### "
        " ## "
        "##  "
        "### "

        "### "
        " ## "
        "  # "
        "### "

        "# # "
        "# # "
        "### "
        "  # "

        "### "
        "##  "
        "  # "
        "##  "

        "### "
        "#   "
        "### "
        "### "

        "### "
        "  # "
        "  # "
        "  # "

        "### "
        "# # "
        "### "
        "### "

        "### "
        "# # "
        "### "
        "  # "

        " #  "
        "# # "
        "### "
        "# # "

        "##  "
        "# # "
        "## #"
        "### "

        "### "
        "#   "
        "#   "
        "### "

        "##  "
        "# # "
        "# # "
        "##  "

        "### "
        "##  "
        "#   "
        "### "

        "### "
        "##  "
        "#   "
        "#   "

        "### "
        "#   "
        "# # "
        "### "

        "# # "
        "### "
        "# # "
        "# # "

        "### "
        " #  "
        " #  "
        "### "

        "### "
        " #  "
        " #  "
        "##  "

        "# # "
        "##  "
        "##  "
        "# # "

        "#   "
        "#   "
        "#   "
        "### "

        "####"
        "## #"
        "#  #"
        "#  #"

        "#  #"
        "## #"
        "# ##"
        "#  #"

        " #  "
        "# # "
        "# # "
        " #  "

        "##  "
        "# # "
        "##  "
        "#   "

        " ## "
        "#  #"
        "# ##"
        " ###"

        "##  "
        "# # "
        "##  "
        "# # "

        "### "
        "##  "
        " ## "
        "### "

        "### "
        " #  "
        " #  "
        " #  "

        "# # "
        "# # "
        "# # "
        "### "

        "# # "
        "# # "
        "# # "
        " #  "

        "#  #"
        "#  #"
        "# ##"
        "####"

        "# # "
        " #  "
        " #  "
        "# # "

        "# # "
        "# # "
        " #  "
        " #  "

        "### "
        "  # "
        " #  "
        "### "
    ;

    unsigned short codes[128];

    for(int i = 0; i < 128; i++){
        codes[i] = 0;
    }

    for(int i = 0; letters[i] != '\0'; i++){
        unsigned short num = 0;
        int offset = 0;
        for(int j = (i+1)*16-1; j >= (i)*16; j--){
            num |= (letterPixels[j]!=' ') << offset;
            offset+=4;
            if(offset >= 16){
                offset -= 15;
            }
        }
        codes[letters[i]] = num;
    }

    printf("#include \"letterCodes.h\"\nconst unsigned short letterCodes[] = {");
    for(int i = 0; i < 127; i++){
        printf("0x%X, ", codes[i]);
    }
    printf("0x%X", codes[127]);
    printf("};\n");
    

    return 0;
}

#endif
