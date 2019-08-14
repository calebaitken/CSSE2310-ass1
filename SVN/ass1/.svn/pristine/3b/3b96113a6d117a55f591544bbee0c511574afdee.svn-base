//
// Created by caleb on 2019-08-01.
//

#ifndef ASS1_BARK_H
#define ASS1_BARK_H

struct gameStatus {
    int width;
    int height;
    int cardsDrawn;
    int turnStatus;
};
typedef struct gameStatus GameStatus;

int main(int argc, char** argv);

int loadGame(char* deckfile, char* p1type, char* p2type);
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type);
int saveGame();
int loadDeck(char* deckfile);

char* drawCard(char playerHand);
void displayBoard();

char* concatCharPnt(int argc, char* argv, ...);

void allocateBoard(int height, int width);
void allocateDeck(int cardc);
void deallocateAll();

#endif //ASS1_BARK_H
