//
// Created by caleb on 2019-08-01.
//

#include <ctype.h>
#include "bark.h"

/**
 * Function: main
 * --------------
 * Main function of program
 *      - verify number of args
 *      - verify types of args
 *      - verify I/O w/ deckfile
 *      - verify I/O w/ savefile
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
        return 0;
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
        if (isalpha(argv[2]) || isalpha(argv[3])) {
            // width or height are not numbers
            return 1;
        }
        newGame(argv[1], (int)argv[2], (int)argv[3], argv[4], argv[5]);
    }

    return 0;
}

int loadGame(char* deckfile, char* p1type, char* p2type) {
    return 0;
}

int newGame(char* deckfile, int width, int height, char* p1type, char* p2type) {
    return 0;
}