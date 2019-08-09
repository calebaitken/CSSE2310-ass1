//
// Created by caleb on 2019-08-01.
//

#ifndef ASS1_BARK_H
#define ASS1_BARK_H

struct Game {
    int width;
    int height;
    int cardsDrawn;
    int turnStatus;
};

int main(int argc, char** argv);

int loadGame(char* deckfile, char* p1type, char* p2type);
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type);

char* concatCharPnt(int argc, char* argv, ...);

void writeGameStatus(FILE* gamefile);

#endif //ASS1_BARK_H
