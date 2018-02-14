#!/usr/bin/env bash
g++ makeLetterCodes.cpp -DactuallyMakeLetterCodes -o makeLetterCodes
./makeLetterCodes > letterCodes.cpp