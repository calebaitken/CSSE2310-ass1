//
// Created by caleb on 2019-08-01.
//

#ifndef ASS1_BARK_H
#define ASS1_BARK_H

#define EXPECTED_ARGS_HIGH 6
#define EXPECTED_ARGS_LOW 4
#define MAX_CARD_LEN 2
#define MAX_CARDS_IN_HAND 6
#define CARDS_IN_STARTING_HAND 5

#define ERR1_MSG "Usage:\tbark savefile p1type p2type\n\tbark deck width height p1type p2type\n"
#define ERR2_MSG "Incorrect arg types\n"
#define ERR3_MSG "Unable to parse deckfile\n"
#define ERR4_MSG "Unable to parse savefile\n"

typedef struct gameStatus {
    int width;
    int height;
    int cardsDrawn;
    int turnStatus;
    int playerOneType;
    int playerTwoType;
} GameStatus;

int main(int argc, char** argv);

int loadGame(char* savefile, char* p1type, char* p2type);
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type);
int saveGame();
void loadDeck(char* deckfile);

void displayBoard();
void displayHand(char** playerHand);

void drawCard(char** playerHand);
void playTurn(int playerType);

char* concatCharPnt(int argc, char* argv, ...);

void allocateBoard(int height, int width);
void allocateDeck(int cardc);
void allocateHands();
void deallocateAll();

#endif //ASS1_BARK_H
