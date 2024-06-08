#include "DisneyCharacter.h"
#include "string"

using namespace std;

#define MAX_LENGTH 50 
#define TRUNCATE_LENGTH 46
#define NUMBER_of_PLACE 6

DisneyCharacter::DisneyCharacter(string newName, string newCreationDate, int NewNumMovies, char newWhichPark)
{	
	bool isDateValid = true;

	if (newName.length() <= MAX_LENGTH)
	{
		name = newName;
	}
	else   
	{
		name = newName.substr(0, TRUNCATE_LENGTH) + " ...";
	}

	if (newCreationDate.length() == 10
		&& newCreationDate[4] == '-'
		&& newCreationDate[7] == '-')
	{
		string yy = newCreationDate.substr(0, 4);
		string mm = newCreationDate.substr(5, 2);
		string dd = newCreationDate.substr(8, 2);		

		for (int i = 0; i < yy.length(); i++)
		{
			if (!isdigit(yy[i]))
			{
				isDateValid = false;
			}
		}
		for (int i = 0; i < mm.length(); i++)
		{
			if (!isdigit(mm[i]))
			{
				isDateValid = false;
			}
		}
		for (int i = 0; i < dd.length(); i++)
		{
			if (!isdigit(dd[i]))
			{
				isDateValid = false;
			}
		}		
	}
	else
	{
		isDateValid = false;
	}
	if (isDateValid)
	{
		creationDate = newCreationDate;
	}
	else
	{
		creationDate = "";
	}

	if (NewNumMovies >= 0)
	{
		numMovies = NewNumMovies;
	}
	else
	{
		numMovies = 0;
	}


	if (newWhichPark == 'M' || newWhichPark == 'S'
		|| newWhichPark == 'S' || newWhichPark == 'E'
		|| newWhichPark == 'C' || newWhichPark == 'N')
	{
		whichPark = newWhichPark;
	}
	else
	{
		whichPark = 'N';
	}
}

DisneyCharacter::DisneyCharacter(string newName, string newCreationDate)
{
	bool isDateValid = true;

	if (newName.length() <= MAX_LENGTH)
	{
		name = newName;
	}
	else
	{
		name = newName.substr(0, TRUNCATE_LENGTH) + " ...";
	}

	if (newCreationDate.length() == 10
		&& newCreationDate[4] == '-'
		&& newCreationDate[7] == '-')
	{
		string yy = newCreationDate.substr(0, 4);
		string mm = newCreationDate.substr(5, 2);
		string dd = newCreationDate.substr(8, 2);

		for (int i = 0; i < yy.length(); i++)
		{
			if (!isdigit(yy[i]))
			{
				isDateValid = false;
			}
		}
		for (int i = 0; i < mm.length(); i++)
		{
			if (!isdigit(mm[i]))
			{
				isDateValid = false;
			}
		}
		for (int i = 0; i < dd.length(); i++)
		{
			if (!isdigit(dd[i]))
			{
				isDateValid = false;
			}
		}
	}
	else
	{
		isDateValid = false;
	}
	if (isDateValid)
	{
		creationDate = newCreationDate;
	}
	else
	{
		creationDate = "";
	}

	numMovies = 0;
	whichPark = 'N';
}

DisneyCharacter::~DisneyCharacter()
{
	printf("%s destroyed\n", name.c_str());
}

string DisneyCharacter::GetName(void)
{	
	return name;
}

string DisneyCharacter::GetCreationDate(void)
{
	return creationDate;
}
int DisneyCharacter::GetNumMovies(void) 
{
	return numMovies;
}
char DisneyCharacter::GetWhichPark(void) 
{
	return whichPark; // can I do this without copy? may they access the address and change it?
}

bool DisneyCharacter::SetNumMovies(int newNum)
{
	bool retCode = false;
	if (newNum >= 0)
	{
		numMovies = newNum;
		retCode = true;
	}
	return(retCode);
}
bool DisneyCharacter::SetWhichPark(char newPark)
{
	bool retCode = false;
	if (newPark == 'M' || newPark == 'S'
		|| newPark == 'S' || newPark == 'E'
		|| newPark == 'C' || newPark == 'N')
	{
		whichPark = newPark;
		retCode = true;
	}
	return(retCode);
}

void DisneyCharacter::ShowInfo(void)
{
	char shortcut[] = { 'M', 'S', 'A', 'E', 'C', 'N' };
	const char* fullname[] = { "Magic Kingdom", "Disney Studios", "Animal Kingdom",
		"Epcot", "California Adventure", "the character is not placed" };
	char fullNameOfPlace[MAX_LENGTH] = "";

	for (int i = 0; i < NUMBER_of_PLACE; i++)
	{
		if (whichPark == shortcut[i])
		{
			strcpy_s(fullNameOfPlace, MAX_LENGTH, fullname[i]);
			break;
		}
	}

	printf("Character Name\t\t\t\t\t\t: %s\n", name.c_str());
	printf("Character creationDate\t\t\t\t\t: %s\n", creationDate.c_str());
	printf("The number of movies that the character has been in\t: %d\n", numMovies);
	printf("Character can be found in\t\t\t\t: %s\n\n", fullNameOfPlace);
}
bool DisneyCharacter::PlaceCharacter(char whichPark)
{
	return SetWhichPark(whichPark);
}
void DisneyCharacter::SameMovies(DisneyCharacter& anotherCharacter)
{
	SetNumMovies(anotherCharacter.numMovies);
}