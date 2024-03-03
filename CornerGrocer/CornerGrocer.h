/*
* John Miller
* CS - 210
* Project 3
* February 25, 2024
* CornerGrocer.h
*/

using namespace std;
#ifndef CORNER_GROCER_H // Header guard
#define CORNER_GROCER_H
// Necessary Libraries
#include<string>
#include<map>
#include<iostream>
#include<fstream>
#include<iomanip>

class CornerGrocer
{
	public:
		int ReadFile(string t_inFile, string t_outFile);
		int Driver();
		bool CornerSwitch(int t_input);

	private:
		map<string, int> m_groceryList; // Map holds a string (itemName) and int (Frequency)
		void DisplayMenu();
		string FormatSearch(string t_input);
		void PrintHistogram();
		void SearchAndPrint();
		void PrintAll();
		void ContinueProgram();
};
#endif // !CORNER_GROCER_H
