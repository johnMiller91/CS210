/*
* John Miller
* CS - 210
* Project 3
* February 25, 2024
* CornerGrocer.cpp
*/

using namespace std;
#include "CornerGrocer.h"

int CornerGrocer::ReadFile(string t_inFile, string t_outFile)
{
	const int OUTPUT_FILE_FAILURE = 2; // Indicates file failed opening out file
	const int INPUT_FILE_FAILURE = 1; // Indicates file failed opening in file
	ifstream inFS; // Declare in-stream
	ofstream outFS; // Declare out-stream
	string itemName; // Holds the item name read from input file

	inFS.open(t_inFile); // Open the infile
	if (!(inFS.is_open())) // Print failure if file is unable to be opened
	{
		cout << "Unable to open file" << endl;
		return INPUT_FILE_FAILURE;
	}

	while (inFS >> itemName) // Keep Reading names until failure 
	{
		m_groceryList[itemName]++; // Either add to map or increment value associated with the key
	}

	inFS.close(); // Close infile

	outFS.open(t_outFile); // Open outfile
	if (!outFS.is_open()) // Print failure message if file outfile is unopened
	{
		cout << "Unable to open write file" << endl;
		return OUTPUT_FILE_FAILURE;
	}

	for (const auto& product : m_groceryList) // Iterate over the map
	{
		outFS << product.first << " " << product.second << endl; // Write Key: Value \n on outfile
	}

	outFS.close(); // Close outfile

	return 0;
}

//Function displays menu options
void CornerGrocer::DisplayMenu()
{
	// Hold strings displaying menu options
	string option1 = "|(1) Search For an Item       |";
	string option2 = "|(2) Print Item Frequency List|";
	string option3 = "|(3) Print Histogram          |";
	string option4 = "|(4) Quit                     |";
	
	// Print menu options
	cout << "*********** Options ***********" << endl;
	cout << setfill('-') << setw(31) << "" << endl;
	cout << option1 << endl << option2 << endl << option3 << endl << option4 << endl;
	cout << setfill('-') << setw(31) << "" << endl;
	cout << "******** Select 1 - 4 *********" << endl;
}

// Calls function to display menu options and validate user enters an acceptable input.
int CornerGrocer::Driver()
{
	int userInput; // Holds user input

	this->DisplayMenu(); // Prints menu options

	// Loops until valid input is recieved (An int between 1-4)
	while ((!(cin >> userInput)) || (userInput < 1) || (userInput > 4))
	{
		cin.clear(); // Clear error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore any input left in-stream
		cout << "Error: Must select 1 - 4" << endl; // Print error message
		this->DisplayMenu(); // Print menu options
	}

	return userInput; // Return users validated selection
}

// Prints the histogram formatted as a table with '*'
void CornerGrocer::PrintHistogram()
{
	int i; // For Loop

	cout << setfill('-') << setw(25) << "" << endl;
	cout << "|       Histogram       |" << endl;
	cout << setfill('-') << setw(25) << "" << endl;

	for (const auto& pair : m_groceryList) // iterate over the map
	{
		cout << setfill(' ') << setw(12) << left << pair.first << "| "; // Output key
		for (i = 0; i < pair.second; ++i)
		{
			cout << "*"; // Print value amout of '*'
		}
		cout << setw(11 - pair.second) << right << "|" << endl; // format end of row so that there '|' is the same distance from the last '*'
	}

	cout << setfill('-') << setw(25) << "" << endl; // Bottom of table
	this->ContinueProgram(); // Calls function that requires user to hit enter to continue
}

// Function allows the user to search for a product and see the frequency
// Allows the search to be case insensitive
void CornerGrocer::SearchAndPrint()
{
	string userInput; // Hold users search

	cout << "Enter Search: "; // Prompt user to switch
	cin >> userInput;
	userInput = this->FormatSearch(userInput); // Calls function to format search so that first char is upper and rest are lower
	auto mapIterator = m_groceryList.find(userInput); // Iterates over map searching for a match

	if (mapIterator != m_groceryList.end()) // if match is found
	{
		cout << mapIterator->first << ": " << mapIterator->second << endl; // Print key: value of match
	}
	else
	{
		cout << "Could not find a match for " << userInput << endl; // No match found
	}

	this->ContinueProgram(); // Function requires user to hit enter
}

// Function prints the frequency of all unique items read in
void CornerGrocer::PrintAll()
{
	cout << setfill('-') << setw(18) << "" << endl;

	for (const auto& pair : m_groceryList) // Iterates over map
	{
		// Formats list so all item values are started at the same point for readability
		cout << "|" << left << setfill(' ') << setw(12) << pair.first;
		cout << "| " << right << setw(2) << pair.second << "|" << endl;
		cout << setfill('-') << setw(18) << "" << endl;
	}

	this->ContinueProgram(); // Requires user to hit enter to continue
}

// Directs user input
bool CornerGrocer::CornerSwitch(int t_input)
{
	switch (t_input) // Switch board for menu options
	{
	case 1:
		this->SearchAndPrint(); // Search and print for an item
		break;
	case 2:
		this->PrintAll(); // Print the frequency of all items
		break;
	case 3:
		this->PrintHistogram(); // Print a histogram
		break;
	case 4:
		cout << "Quitting Program..." << endl;
		return false; // Quit Program
	}
	return true;
}

// Formats user search to match the infile 
string CornerGrocer::FormatSearch(string t_input)
{
	unsigned int i; // For loop
	string formattedSearch; // Holds formatted string
	if (t_input == "") // In case the string is empty
	{
		return "";
	}

	formattedSearch = t_input; // Initilaze the variable to the user input

	formattedSearch[0] = toupper(formattedSearch[0]); // Capatalize first letter

	for (i = 1; i < formattedSearch.size(); ++i) // iterate over string started from character at position 1
	{
		formattedSearch[i] = tolower(formattedSearch[i]); // Make sure all letters are lowercase
	}

	return formattedSearch; // Return formatted string
}

// Function requires until user hits enter
void CornerGrocer::ContinueProgram()
{
	char userInput;

	cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear in-stream

	cout << "Press Enter to Continue..."; // Prompt user to hit enter

	// Loops until user hits enter
	do {
		userInput = getchar();
	} while (userInput != '\n');

	cout << endl;
}