//
// Created by caleb on 2019-08-01.
//

#include <ctype.h>
#include <unistd.h>
#include <string.h>

#include "bark.h"

/*
 * Function: main
 * --------------
 * TODO: Main function of program
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
    char* one = "one";
    char* two = "two";
    char result = concatCharPnt(one, two);
    if (strcmp(&result, "onetwo") == 1) {
        return 1;
    }
    return 0;
}

/*
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
*/

/*
 * CAN ONLY OPEN FILES IN MOSS IF GIVEN ABSOLUTE PATH, OR IS IN THE SAME DIRECTORY AS
 * EXECUTABLE FILE.
 *
 * TODO: needs cleaner solution
 */
int loadGame(char* deckfile, char* p1type, char* p2type) {
    gamefile = fopen(deckfile, "r+");
    if (gamefile == NULL) {
        int buffersize = strlen(getcwd(cwd, sizeof(cwd))) + strlen("/") + strlen(deckfile) + 1;
        char strbuf[buffersize];
        strcpy(strbuf, getcwd(cwd, sizeof(cwd)));
        strcat(strbuf, "/");
        strcat(strbuf, deckfile);
        gamefile = fopen(strbuf, "r+");
        if (gamefile == NULL) {
            return 100;
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
    int buffersize = strlen(getcwd(cwd, sizeof(cwd))) + strlen("/") + strlen(deckfile) + 1;
    char strbuf[buffersize];
    strcpy(strbuf, getcwd(cwd, sizeof(cwd)));
    strcat(strbuf, "/");
    strcat(strbuf, deckfile);
    gamefile = fopen(strbuf, "w+");
    return 0;
}

char concatCharPnt(char* args, ...) {
    va_list ap;
    int buffersize = 1;

            va_start(ap, args);
    while(args != 0) {
        buffersize += strlen(va_arg(ap, char*));
    }
            va_end(ap);

    char result[buffersize];

            va_start(ap, args);
    strcpy(result, va_arg(ap, char*));
    while(args !=0) {
        strcat(result, va_arg(ap, char*));
    }
            va_end(ap);

    return *result;
}