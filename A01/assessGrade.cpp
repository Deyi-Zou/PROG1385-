/* ======================================================== */
/* PURPOSE  : This file contains all of the various         */
/*            functions used to assess student grade        */
/* ======================================================== */

#define OOPS  // only define OOPS here, preventing multiple declearation of golbal varibles

#include <stdio.h>
#include <string.h>
#include "assessGrade.h"

// since the globals now only are needed in this file - they can be declared at the top of this .cpp
double numericalGrade = 0.0;
char letterGrade[MAXIMUM_CHAR] = { 0 };
int eachAssigGrade[5] = { 0 };
char specialState[MAXIMUM_CHAR] = { 0 };

// function to initialize (and re-initialze) the variables to each input from the user
void initializeInputState(void)
{
	numericalGrade = 0.0;
	strcpy_s(letterGrade, MAXIMUM_CHAR, "");
	for (int i = 0; i < 5; i++)
	{
		eachAssigGrade[i] = 0;
	}
	strcpy_s(specialState, MAXIMUM_CHAR, "");
}

/* ================================================================== */
/* FUNCTION : parseUserInput( input string)                           */
/* PURPOSE  : This function takes string input and determines         */
/*            what kind of input the user entered and                 */
/*            extracted the data from the user’s input string         */
/* INPUTS   : a C-Style string                                        */
/* RETURNS  : extracted content from input string or error statement  */
/* ================================================================== */
int parseUserInput(char* record)
{
	int isFloat = 0;
	for (int i = 0; i < strlen(record); i++)
	{
		if (record[i] == '.')
		{
			isFloat = 1;
		}
	}

	if (isFloat)
	{ // check if an acceptable floating point number may be “60.5” or “12500.6” or “-12.76”
		sscanf_s(record, "%lf", &numericalGrade);
		return CASE_1;
	}
	else if (sscanf_s(record, "%d %d %d %d %d", &eachAssigGrade[0], &eachAssigGrade[1],
		&eachAssigGrade[2], &eachAssigGrade[3], &eachAssigGrade[4]) != 0)
	{ // check if an acceptable set of integers may be “1 2 3” or “673 -23 70 30 20”
		return CASE_3;
	}
	else if (sscanf_s(record, "%s", letterGrade, MAXIMUM_CHAR) == 1)
	{ // check if an acceptable alpha-only input may be “A+”, “I/P” or “Hello”
		return CASE_2;
	}
	else {
		return ERROR;
	}
};

/* ============================================================ */
/* FUNCTION : assessGrade( numericalGrade)                      */
/* PURPOSE  : This function takes the double data extracted by  */
/*            parseUserInput fuction and examine if the student */
/*            passed or failed or had a special situation.      */
/* INPUTS   : numericalGrade - double float,                    */
/*                             value between 0 and 100          */
/* RETURNS  : an int, indicates the grade state                 */
/* ============================================================ */
int assessGrade(double numericalGrade)
{
	if (numericalGrade >= 54.50 && numericalGrade <= 100.0)
	{
		return PASS;
	}
	else if (numericalGrade >= 0.0 && numericalGrade < 54.50)
	{
		return FAIL;
	}
	else
	{
		return ERROR;
	}
}

/* ============================================================== */
/* FUNCTION : assessGrade( letterGrade)                           */
/* PURPOSE  : This function takes the string data extracted by    */
/*            parseUserInput fuction and examine if the student   */
/*            passed or failed or had a special situation.        */
/* INPUTS   : letterGrade - string, below are valid               */
/*                         "A+", "A", "B+", "B", "C+", "C",       */
/*                         "D", "F", "I", "Q", "AU", "DNA", "I/P" */
/* RETURNS  : an int, indicates the grade state                   */
/* ============================================================== */
int assessGrade(char* letterGrade)
{
	char* ptWhereCR = strchr(letterGrade, '\n');
	if (ptWhereCR != NULL)
	{
		*ptWhereCR = '\0';
	}
	int sizeV = 8;
	const char* validGrade[] = { "A+", "A", "B+", "B", "C+", "C", "D", "F" };
	double grades[] = { 95.0, 85.0, 77.0, 72.0, 67.0, 62.0, 57.0, 50 };
	int sizeS = 5;
	const char* specialSituations[] = { "I", "Q", "AU", "DNA", "I/P" };
	const char* situations[] = { "Incomplete", "Withdrawal After Drop/Refund Date",
	"Audit Condition", "Did Not Attend", "In Process" };

	for (int i = 0; i < sizeV; i++)
	{
		if (strcmp(validGrade[i], letterGrade) == 0)
		{
			numericalGrade = grades[i];
			return assessGrade(numericalGrade); // call the "worker-bee" function
		}
	}
	for (int j = 0; j < sizeS; j++)
	{
		if (strcmp(specialSituations[j], letterGrade) == 0)
		{
			strcpy_s(specialState, MAXIMUM_CHAR, situations[j]);
			return SPECIAL;
		}
	}

	return ERROR;
}

/* ============================================================== */
/* FUNCTION : assessGrade( eachAssigGrade)                        */
/* PURPOSE  : This function takes the int array data extracted    */
/*            by parseUserInput fuction and examine if the        */
/*            student passed or failed or had a special situation */
/* INPUTS   : eachAssigGrade - int array,                         */
/*                             value between 0 and 100            */
/* RETURNS  : an int, indicates the grade state                   */
/* ============================================================== */
int assessGrade(int eachAssigGrade[])
{
	// what if input 6 number ?
	int i = 0;
	int sum = 0;
	while (eachAssigGrade[i] != NULL)
	{
		if (eachAssigGrade[i] < 0 || eachAssigGrade[i] > 100)
		{
			return ERROR;
		}
		sum += eachAssigGrade[i];
		i++;
	}

	numericalGrade = (double)sum / 5;  // transfer int to double
	return assessGrade(numericalGrade);        // call the "worker-bee" function
}


/* =================================================================  */
/* FUNCTION : showGrade( retCodeP)                                    */
/* PURPOSE  : This function takes the return code of parseUserInput() */
/*            and use it to determine which overload function should  */
/*            be called then output the grade                         */
/* INPUTS   : retCodeP - int, return of parseUserInput()              */
/* RETURNS  : None                                                    */
/* ================================================================== */

void showGrade(int retCodeP) 
{
	int retCodeA = 0;
	switch (retCodeP)
	{
	case CASE_1:
		retCodeA = assessGrade(numericalGrade);
		break;
	case CASE_2:
		retCodeA = assessGrade(letterGrade);
		break;
	case CASE_3:
		retCodeA = assessGrade(eachAssigGrade);
		break;
	case ERROR:
		printf("**ERROR : Invalid Input\n");    
		break;
	default:
		break;
	}
	// ouput according to the return code
	switch (retCodeA)
	{
	case PASS:
		printf("Student achieved %.2f%% which is a %s condition.\n", numericalGrade, "PASS");
		break;
	case FAIL:
		printf("Student achieved %.2f%% which is a %s condition.\n", numericalGrade, "FAIL");
		break;
	case ERROR:
		printf("**ERROR : Invalid Input\n");   
		break;
	case SPECIAL:
		printf("Student has Special Situation : %s (%s)\n", letterGrade, specialState);
		break;
	default:
		break;
	}
}

