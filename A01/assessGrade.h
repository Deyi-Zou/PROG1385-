/* ======================================================== */
/* This file contains the prototypes for the 3 overloaded   */
/* functions the user input parsing function as well as any */
/* other defines or constants                               */
/* ======================================================== */

// constants
#define MAXIMUM_CHAR 101

// function prototypes for overload functions
// for examining if the student passed or failed or had a special situation
void assessGrade(double);
void assessGrade(char *);
void assessGrade(int[]);

// function prototypes for determining the input and extract data
void parseUserInput(char*);
