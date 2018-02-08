#!/usr/bin/env bash
g++ makeLetterCodes.cpp -DactuallyMakeLetterCodes -o makeLetterCodes
./makeLetterCodes > letterCodes.cpp
g++ cursesGame.cpp letterCodes.cpp -O3 -o cursesGame -lncurses