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

char charBuffer[255];

struct Game {
    int width;
    int height;
    int cardsDrawn;
    int turnStatus;
} gameStatus;

char** gameBoard;

char* p1Hand;
char* p2Hand;

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
    } else if (argc > 6) {
        //too many arguments given
        return 1;
    } else if (argc > 4 && argc < 6) {
        // invalid combination of arguments
        return 1;
    }

    // handle arg values
    if (argc == 4) {
        loadGame(argv[1], argv[2], argv[3]);
    } else if (argc == 6) {
        if (!(isdigit(*argv[2]) && isdigit(*argv[3]))) {
            // width or height are not numbers
            return 2;
        }
        newGame(argv[1], (int)*argv[2], (int)*argv[3], argv[4], argv[5]);
    }

    return 0;
}

/*
 * CAN ONLY OPEN FILES IN MOSS IF GIVEN ABSOLUTE PATH, OR IS IN THE SAME DIRECTORY AS
 * EXECUTABLE FILE.
 *
 * TODO: needs cleaner solution
 */
int loadGame(char* deckfile, char* p1type, char* p2type) {
    gamefile = fopen(deckfile, "r+");
    if (gamefile == NULL) {
        gamefile = fopen(concatCharPnt(3, getcwd(charBuffer, sizeof(charBuffer)), "/", deckfile), "r+");
        if (gamefile == NULL) {
            return 3;
        }
    }

    // retrieve width from savefile
    fscanf(gamefile, "%s", charBuffer);
    gameStatus.width = (int) charBuffer;

    // retrieve height from savefile
    fscanf(gamefile, "%s", charBuffer);
    gameStatus.height = (int) charBuffer;

    // retrieve number of cards drawn from the deck
    fscanf(gamefile, "%s", charBuffer);
    gameStatus.cardsDrawn = (int) charBuffer;

    // retrieve player turn indicator
    fscanf(gamefile, "%s", charBuffer);
    gameStatus.turnStatus = (int) charBuffer;

    // retrieve deckname TODO: handle this
    fgets(charBuffer, 255, gamefile);

    // retrieve player one's hand
    fgets(charBuffer, 255, gamefile);
    strcpy(p1Hand, charBuffer);

    // retrieve player two's hand
    fgets(charBuffer, 255, gamefile);
    strcpy(p2Hand, charBuffer);

    //int i;
    gameBoard = malloc(gameStatus.height * sizeof(char *));
    for (int i = 0; i < gameStatus.height; i++) {
        gameBoard[i] = malloc(gameStatus.width * (sizeof(char) * 2));
    }

    return 0;
}

/*
 *
 *
 * TODO: create .deck file
 */
int newGame(char* deckfile, int width, int height, char* p1type, char* p2type) {
    gamefile = fopen(concatCharPnt(4, getcwd(charBuffer, sizeof(charBuffer)), "/", deckfile, ".deck"), "w+");
    return 0;
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

int WriteGameStatus(FILE* gamefile) {

}