//
// Created by caleb on 2019-08-01.
//

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
        savefile = argv[1];
        p1type = argv[2];
        p2type = agrv[3];
    } else if (argc == 6) {
        deckfile = argv[1];
        width = argv[2];
        height = argv[3];
        p1type = argv[4];
        p2type = argv[5];
    }

    return 0;
}

int init()