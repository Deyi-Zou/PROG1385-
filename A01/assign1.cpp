#include <stdio.h>
#include <string.h>
#include "assessGrade.h"

/* =================================================================  */
/* FUNCTION : main                                                    */
/* PURPOSE  : loop requesting the user’s input, call parseUserInput() */
/*            to determine the type of user input then call           */
/*            assessGrade() to examine the grade and call showGrade() */
/*            show the result.                                        */
/* RETURNS  : 0 - OKAY status                                         */
/* =================================================================  */
int main(void)
{
    // cycle until the user enters “X” to exit the program:
    while (true)
    {
        // global variables reinitialize
        numericalGrade = 0.0;
        strcpy_s(letterGrade, MAXIMUM_CHAR, "");
        for (int i = 0; i < 5; i++)
        {
            eachAssigGrade[i] = 0;
        }
        strcpy_s(specialState, MAXIMUM_CHAR, "");

        char record[MAXIMUM_CHAR] = { 0 };
        char inputChar = 'P';
        char fileName[MAXIMUM_CHAR] = { 0 };
        int retCodeP = 0;

        printf("Enter Student's Grade(s) >>>  ");
        fgets(record, sizeof(record), stdin);


        // examine whether user want to exit
        if (sscanf_s(record, "%c", &inputChar, 1) == 1)
        {
            if (inputChar == 'X')
            {
                return EXIT;
            }
        }
        // user is trying to specify an input test file
        if (sscanf_s(record, "%c %s", &inputChar, 1, fileName, MAXIMUM_CHAR) == 2)
        {
            if (inputChar == 'Z')
            { 
                char* ptWhereCR = strchr(fileName, '\n');
                if (ptWhereCR != NULL)
                {
                    *ptWhereCR = '\0';
                }

                FILE* pt;
               if (fopen_s(&pt, fileName, "r") != 0)
                {
                    printf("%s File I/O ERROR.\n", fileName);
                    continue;
                }
                while (fgets(record, MAXIMUM_CHAR, pt) != NULL)
                {
                    retCodeP = parseUserInput(record);
                    showGrade(retCodeP);
                }
                if (!feof(pt))
                {
                    printf("%s File I/O ERROR.\n", fileName);
                }
                if (fclose(pt) != 0)
                {
                    printf("%s File I/O ERROR.\n", fileName);
                }
                continue;
            }            
        }
        // If not “X” or “Z …” then pass the user input into parseUserInput() for further processing
        retCodeP = parseUserInput(record);
        showGrade(retCodeP);
    }
    return 0;
}
