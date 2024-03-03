/*
* John Miller
* CS - 210
* Project 3
* February 25, 2024
* Main Loop
*/

using namespace std;
#include "CornerGrocer.h"

int main()
{
	const int INPUT_FILE_FAILURE = 1; // Indicates infile was not opened
	const int OUTPUT_FILE_FAILURE = 2; // Indicates outfile was not opened
	int fileIndicator; // Variable indicates if there was an fstream failure
	CornerGrocer grocer; // Initilaze a CornerGrocer obj called grocer
	bool runProgram = true; // Loop variable
	int userSelection; // Holds users menu choice

	fileIndicator = grocer.ReadFile("CS210_Project_Three_Input_File.txt", "frequency.dat"); // Calls function to read/write a file and creates a map from the data
	switch (fileIndicator) // Switch checks to make sure files were successfully read and written
	{
	case 1:
		return INPUT_FILE_FAILURE;
		break;
	case 2:
		return OUTPUT_FILE_FAILURE;
		break;
	}
	
	// Loops until user quits
	while (runProgram)
	{
		userSelection = grocer.Driver(); // Function call displays menu, gets, and validates users selection
		runProgram = grocer.CornerSwitch(userSelection); // Directs user selection returns false if user quits exiting loop
	}

	return 0;
}