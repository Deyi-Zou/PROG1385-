
#include "string"
using namespace std;

class DisneyCharacter
{
private:
	string name;
	string creationDate;
	int numMovies;
	char whichPark;

public:
	DisneyCharacter(string newName, string newCreationDate, int NewNumMovies, char newWhichPark);
	DisneyCharacter(string newName, string newCreationDate);
	~DisneyCharacter();

	string GetName(void);
	string GetCreationDate(void);
	int GetNumMovies(void);
	char GetWhichPark(void);

	bool SetNumMovies(int);
	bool SetWhichPark(char);

	void ShowInfo(void);
	bool PlaceCharacter(char whichPark);
	void SameMovies(DisneyCharacter& anotherCharacter);
};