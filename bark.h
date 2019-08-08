//
// Created by caleb on 2019-08-01.
//

#include <stdio.h>
#include <stdarg.h>

#ifndef ASS1_BARK_H
#define ASS1_BARK_H

FILE* gamefile;

char cwd[256];

int main(int argc, char** argv);

int loadGame(char* deckfile, char* p1type, char* p2type);
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type);

char concatCharPnt(int argc, char* args, ...);

#endif //ASS1_BARK_H
