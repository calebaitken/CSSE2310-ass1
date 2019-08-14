//
// Created by caleb on 2019-08-01.
//

#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "bark.h"

FILE* g_gamefile;
FILE* g_deckfile;

char g_charBuffer[255];

GameStatus g_gameStatus;

char*** g_gameBoard;

char** g_deck;
char** g_p1Hand;
char** g_p2Hand;

/*
 * Function: main
 * --------------
 *
 * argc:    number of arguments received
 * argv:    array of argument values
 *
 * returns: zero if no errors in execution
 */
int main(int argc, char** argv) {
    // verify arg count
    if (argc == 1) {
        //function for printing help dialog
        fprintf(stderr, ERR1_MSG);
        exit(1);
    } else if (argc > EXPECTED_ARGS_HIGH) {
        //too many arguments given
        fprintf(stderr, ERR1_MSG);
        exit(1);
    } else if (argc > EXPECTED_ARGS_LOW && argc < EXPECTED_ARGS_HIGH) {
        // invalid combination of arguments
        fprintf(stderr, ERR1_MSG);
        exit(1);
    }

    // may as well do this before opening up our files since it relies on constants
    allocateHands();

    // handle arg values
    if (argc == EXPECTED_ARGS_LOW) {
        loadGame(argv[1], argv[2], argv[3]);
    } else if (argc == EXPECTED_ARGS_HIGH) {
        if (!(isdigit(*argv[2]) && isdigit(*argv[3]))) {
            // width or height are not numbers
            fprintf(stderr, ERR2_MSG);
            exit(2);
        }
        newGame(argv[1], strtol(argv[2], NULL, 10), strtol(argv[3], NULL, 10), argv[4], argv[5]);
    }

    displayBoard();

    displayHand();

    // TODO: handle first move

    // TODO: add game loop with finish condition

    deallocateAll();

    return 0;
}

/**
 * Function loads the current game state from the given terminal arguments.
 *
 * @param savefile  save file to game state from
 * @param p1type    player one type (human/computer)
 * @param p2type    player two type (human/computer)
 * @return          exit code
 */
int loadGame(char* savefile, char* p1type, char* p2type) {
    // open saved game file
    g_gamefile = fopen(savefile, "r+");
    if (g_gamefile == NULL) {
        g_gamefile = fopen(concatCharPnt(3, getcwd(g_charBuffer, sizeof(g_charBuffer)), "/", savefile), "r+");
        if (g_gamefile == NULL) {
            fprintf(stderr, ERR4_MSG);
            exit(4);
        }
    }

    // assign player one type
    if (strcmp(p1type, "h") == 0) {
        g_gameStatus.playerOneType = 0;
    } else if (strcmp(p1type, "a") == 0) {
        g_gameStatus.playerOneType = 1;
    } else {
        fprintf(stderr, ERR2_MSG);
        exit(2);
    }

    // assign player two type
    if (strcmp(p2type, "h") == 0) {
        g_gameStatus.playerTwoType = 0;
    } else if (strcmp(p2type, "a") == 0) {
        g_gameStatus.playerTwoType = 1;
    } else {
        fprintf(stderr, ERR2_MSG);
        exit(2);
    }

    // retrieve width from savefile
    fscanf(g_gamefile, "%d", &g_gameStatus.width);

    // retrieve height from savefile
    fscanf(g_gamefile, "%d", &g_gameStatus.height);

    // retrieve number of cards drawn from the deck
    fscanf(g_gamefile, "%d", &g_gameStatus.cardsDrawn);

    // retrieve player turn indicator
    fscanf(g_gamefile, "%d", &g_gameStatus.turnStatus);

    // retrieve deckname TODO: handle this
    fscanf(g_gamefile, "%s", g_charBuffer);
    loadDeck(g_charBuffer);

    // retrieve player one's hand
    fscanf(g_gamefile, "%s", g_charBuffer);


    // retrieve player two's hand
    fscanf(g_gamefile, "%s", &g_p2Hand);

    allocateBoard(g_gameStatus.height, g_gameStatus.width);

    // get card's from saved file and copy into char*** g_gameBoard
    int i, j;
    for(i = 0; i < g_gameStatus.height; i++) {
        fscanf(g_gamefile, "%s", g_charBuffer);
        for(j = 0; j < g_gameStatus.width; j++) {
            g_gameBoard[j][i][0] = (char)g_charBuffer[j*2];
            g_gameBoard[j][i][1] = (char)g_charBuffer[(j*2)+1];
        }
    }

    return 0;
}

/*
 *
 *
 * TODO: create .deck file
 */
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type) {
    loadDeck(deckfile);
    g_gameStatus.width = width;
    g_gameStatus.height = height;
    g_gameStatus.turnStatus = 1;    // TODO: get a real number
    g_gameStatus.cardsDrawn = 0;

    allocateBoard(g_gameStatus.height, g_gameStatus.width);

    // fill board with blanks
    int i, j;
    for (i = 0; i < g_gameStatus.height; i++) {
        for (j = 0; j < g_gameStatus.width; j++) {
            strcpy(g_gameBoard[j][i], "**");
        }
    }

    return 0;
}

int saveGame() {
    return 0;
}

int loadDeck(char* deckfile) {
    g_deckfile = fopen(deckfile, "r+");
    if(g_deckfile == NULL) {
        g_deckfile = fopen(concatCharPnt(3, getcwd(g_charBuffer, sizeof(g_charBuffer)), "/", deckfile), "r+");
        if (g_deckfile == NULL) {
            fprintf(stderr, ERR3_MSG);
            exit(3);
        }
    }

    int cards, i;
    fscanf(g_deckfile, "%d", &cards);

    allocateDeck(cards);

    for (i = 0; i < cards; i++) {
        fscanf(g_deckfile, "%s", g_deck[i]);
    }

    return 0;
}

/**
 * Display the current state of the board
 */
void displayBoard() {
    int i, j;
    for (i = 0; i < g_gameStatus.height; i++) {
        for (j = 0; j < g_gameStatus.width; j++) {
            printf("%s%s", g_gameBoard[j][i], " ");
        }
        printf("\n");
    }
}

/**
 * Display's the hand of the player about to make a move
 */
void displayHand() {

}

/**
 * Helper function to concatenate strings in C
 * Requires #include <stdarg.h>
 *          #include <stdlib.h>
 *          #include <string.h>
 *
 * @param argc  number of strings to join
 * @param argv  first string to join
 * @param ...   following indefinite number of strings to join
 * @return      the strings joined together
 */
char* concatCharPnt(int argc, char* argv, ...) {
    va_list ap;
    int buffersize = 1;
    int i;

    va_start(ap, argv);
    buffersize += strlen(argv);
    for (i = 1; i < argc; i++) {
        buffersize += strlen(va_arg(ap, char*));
    }
    va_end(ap);

    char* result = malloc(buffersize);

    va_start(ap, argv);
    strcpy(result, argv);
    for (i = 1; i < argc; i++) {
        strcat(result, va_arg(ap, char*));
    }
    va_end(ap);

    return result;
}

/**
 * Allocates memory for a 2D matrix of char*
 *
 * Allocated as gameBoard[width][height]
 *
 * @param gameBoard the matrix to allocate memory for
 * @param height    the height of the matrix
 * @param width     the width of the matrix
 */
void allocateBoard(int height, int width) {
    int i, j;
    g_gameBoard = calloc(width, sizeof(char**));
    for (i = 0; i < width; i++) {
        g_gameBoard[i] = calloc(height, sizeof(char*));
        for(j = 0; j < height; j++) {
            g_gameBoard[i][j] = calloc(MAX_CARD_LEN, sizeof(char));
        }
    }
}

/**
 * Allocates memory for the array of strings
 *
 * @param cardc count of cards in deck
 */
void allocateDeck(int cardc) {
    int i;
    g_deck = calloc(cardc, sizeof(char*));
    for (i = 0; i < cardc; i++) {
        g_deck[i] = calloc(MAX_CARD_LEN, sizeof(char));
    }
}

/**
 * Allocates memory for the array of string representing a player's hand
 */
void allocateHands() {
    int i;
    g_p1Hand = calloc(MAX_CARDS_IN_HAND, sizeof(char*));
    for (i = 0; i < MAX_CARDS_IN_HAND; i++) {
        g_p1Hand[i] = calloc(MAX_CARD_LEN, sizeof(char));
    }

    g_p2Hand = calloc(MAX_CARDS_IN_HAND, sizeof(char*));
    for (i = 0; i < MAX_CARDS_IN_HAND; i++) {
        g_p2Hand[i] = calloc(MAX_CARD_LEN, sizeof(char));
    }
}

/**
 * Free all memory allocations, and closes all open files
 */
void deallocateAll() {
    free(g_gameBoard);
    free(g_deck);
    free(g_p1Hand);
    free(g_p2Hand);
    fclose(g_gamefile);
    fclose(g_deckfile);
}