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

FILE* gamefile;

char g_charBuffer[255];

int MAX_CHAR_LEN = 2;
int EXPECTED_ARGS_HIGH = 6;
int EXPECTED_ARGS_LOW = 4;

GameStatus g_gameStatus;

char*** g_gameBoard;

char p1Hand;
char p2Hand;

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
        return 1;
    } else if (argc > EXPECTED_ARGS_HIGH) {
        //too many arguments given
        return 1;
    } else if (argc > EXPECTED_ARGS_LOW && argc < EXPECTED_ARGS_HIGH) {
        // invalid combination of arguments
        return 1;
    }

    // handle arg values
    if (argc == EXPECTED_ARGS_LOW) {
        loadGame(argv[1], argv[2], argv[3]);
    } else if (argc == EXPECTED_ARGS_HIGH) {
        if (!(isdigit(*argv[2]) && isdigit(*argv[3]))) {
            // width or height are not numbers
            return 2;
        }
        newGame(argv[1], (int)*argv[2], (int)*argv[3], argv[4], argv[5]);
    }

    displayBoard();

    deallocateAll();

    return 0;
}

/**
 * Function loads the current game state from the given terminal arguments.
 *
 * @param deckfile  save file to game state from
 * @param p1type    player one type (human/computer)
 * @param p2type    player two type (human/computer)
 * @return          exit code
 */
int loadGame(char* deckfile, char* p1type, char* p2type) {
    gamefile = fopen(deckfile, "r+");
    if (gamefile == NULL) {
        gamefile = fopen(concatCharPnt(3, getcwd(g_charBuffer, sizeof(g_charBuffer)), "/", deckfile), "r+");
        if (gamefile == NULL) {
            return 3;
        }
    }

    // retrieve width from savefile
    fscanf(gamefile, "%d", &g_gameStatus.width);

    // retrieve height from savefile
    fscanf(gamefile, "%d", &g_gameStatus.height);

    // retrieve number of cards drawn from the deck
    fscanf(gamefile, "%d", &g_gameStatus.cardsDrawn);

    // retrieve player turn indicator
    fscanf(gamefile, "%d", &g_gameStatus.turnStatus);

    // retrieve deckname TODO: handle this
    fscanf(gamefile, "%s", g_charBuffer);

    // retrieve player one's hand
    fscanf(gamefile, "%s", &p1Hand);

    // retrieve player two's hand
    fscanf(gamefile, "%s", &p2Hand);

    allocateBoard(g_gameStatus.height, g_gameStatus.width);

    int i, j;
    for(i = 0; i < g_gameStatus.height; i++) {
        fscanf(gamefile, "%s", g_charBuffer);
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
    gamefile = fopen(concatCharPnt(3, getcwd(g_charBuffer, sizeof(g_charBuffer)), "/", deckfile), "w+");

    g_gameStatus.width = width;
    g_gameStatus.height = height;
    g_gameStatus.turnStatus = 1;    // TODO: get a real number
    g_gameStatus.cardsDrawn = 0;

    int i, j;
    allocateBoard(g_gameStatus.height, g_gameStatus.width);
    for (i = 0; i < g_gameStatus.width; i++) {
        for (j = 0; j < g_gameStatus.height; i++) {
            g_gameBoard[i][j] = "**";
        }
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

int saveGame() {
    return 0;
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
        g_gameBoard[i] = calloc(height, sizeof(char *));
        for(j = 0; j < height; j++) {
            g_gameBoard[i][j] = calloc(MAX_CHAR_LEN, sizeof(char));
        }
    }
}

/**
 * Free all memory allocations, and closes all open files
 */
void deallocateAll() {
    free(g_gameBoard);
    fclose(gamefile);
}