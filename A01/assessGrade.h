/* ======================================================== */
/* This file contains the prototypes for the 3 overloaded   */
/* functions the user input parsing function as well as any */
/* other defines or constants                               */
/* ======================================================== */

// constants
#define MAXIMUM_CHAR 101
#define CASE_1 1
#define CASE_2 2
#define CASE_3 3
#define EXIT 4
#define PASS 5
#define FAIL 6
#define ERROR 7
#define SPECIAL 8


// function prototypes for overload functions
// for examining if the student passed or failed or had a special situation
void assessGrade(double);
void assessGrade(char *);
void assessGrade(int[]);

// function prototypes for determining the input and extract data
void parseUserInput(char*);
