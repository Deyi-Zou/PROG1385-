/* ======================================================== */
/* PURPOSE  : This file contains all of the various         */
/*            functions used to assess student grade        */
/* ======================================================== */

#include <stdio.h>
#include <string.h>
#include "assessGrade.h"

/* ================================================================== */
/* FUNCTION : parseUserInput( input string)                           */
/* PURPOSE  : This function takes string input and determines         */
/*            what kind of input the user entered and                 */
/*            extracted the data from the user’s input string then    */
/*            overload functions                                      */
/* INPUTS   : a C-Style string                                        */
/* RETURNS  : nothing                                                 */
/* ================================================================== */
void parseUserInput(char* record)
{
	double numericalGrade = 0.0;
	char letterGrade[MAXIMUM_CHAR] = { 0 };
	int eachAssigGrade[5] = { 0 };
	int isFloat = 0;


	if (strchr(record, '.') != NULL)
	{
		isFloat = 1;
	}

	if (isFloat)
	{ // check if an acceptable floating point number may be “60.5” or “12500.6” or “-12.76”
		sscanf_s(record, "%lf", &numericalGrade);
		assessGrade(numericalGrade);
	}
	else if (sscanf_s(record, "%d %d %d %d %d", &eachAssigGrade[0], &eachAssigGrade[1],
		&eachAssigGrade[2], &eachAssigGrade[3], &eachAssigGrade[4]) != 0)
	{ // check if an acceptable set of integers may be “1 2 3” or “673 -23 70 30 20”
		assessGrade(eachAssigGrade);
	}
	else if (sscanf_s(record, "%s", letterGrade, MAXIMUM_CHAR) == 1)
	{ // check if an acceptable alpha-only input may be “A+”, “I/P” or “Hello”
		assessGrade(letterGrade);
	}
	else {
		printf("**ERROR : Invalid Input\n");
	}
};

/* ============================================================ */
/* FUNCTION : assessGrade( numericalGrade)                      */
/* PURPOSE  : This function takes the double data extracted by  */
/*            parseUserInput fuction and examine if the student */
/*            passed or failed or had a special situation.      */
/*            then print it.                                    */
/* INPUTS   : numericalGrade - double float,                    */
/*                             value between 0 and 100          */
/* RETURNS  : nothing                                           */
/* ============================================================ */
void assessGrade(double numericalGrade)
{
	if (numericalGrade >= 54.50 && numericalGrade <= 100.0)
	{
		printf("Student achieved %.2f%% which is a %s condition.\n", numericalGrade, "PASS");
	}
	else if (numericalGrade >= 0.0 && numericalGrade < 54.50)
	{
		printf("Student achieved %.2f%% which is a %s condition.\n", numericalGrade, "FAIL");
	}
	else
	{
		printf("**ERROR : Invalid Input\n");
	}
}

/* ============================================================== */
/* FUNCTION : assessGrade( letterGrade)                           */
/* PURPOSE  : This function takes the string data extracted by    */
/*            parseUserInput fuction and examine if the student   */
/*            passed or failed or had a special situation,        */
/*            then print it.                                      */
/* INPUTS   : letterGrade - string, below are valid               */
/*                         "A+", "A", "B+", "B", "C+", "C",       */
/*                         "D", "F", "I", "Q", "AU", "DNA", "I/P" */
/* RETURNS  : nothing                                             */
/* ============================================================== */
void assessGrade(char* letterGrade)
{
	char specialState[MAXIMUM_CHAR] = { 0 };
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
			assessGrade(grades[i]); // call the "worker-bee" function
			return;
		}
	}
	for (int j = 0; j < sizeS; j++)
	{
		if (strcmp(specialSituations[j], letterGrade) == 0)
		{
			strcpy_s(specialState, MAXIMUM_CHAR, situations[j]);
			printf("Student has Special Situation : %s (%s)\n", letterGrade, specialState);
			return;
		}
	}

	printf("**ERROR : Invalid Input\n");
}

/* ============================================================== */
/* FUNCTION : assessGrade( eachAssigGrade)                        */
/* PURPOSE  : This function takes the int array data extracted    */
/*            by parseUserInput fuction and examine if the        */
/*            student passed or failed or had a rrror input       */
/*            then print it.                                      */
/* INPUTS   : eachAssigGrade - int array,                         */
/*                             value between 0 and 100            */
/* RETURNS  : nothing                                             */
/* ============================================================== */
void assessGrade(int eachAssigGrade[])
{
	// what if input 6 number ?
	int i = 0;
	int sum = 0;
	while (i < 5)
	{
		if (eachAssigGrade[i] < 0 || eachAssigGrade[i] > 100)
		{
			printf("**ERROR : Invalid Input\n");
			return;
		}
		sum += eachAssigGrade[i];
		i++;
	}
	assessGrade((double)sum / 5);        // call the "worker-bee" function, transfer int to double
}


