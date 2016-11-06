// ===========================================
// Created: October 12, 2016
// Sheila Doherty
// Homework Assignment #5: Binary Search Tree
// Included Files: MovieTree.cpp & DriverHW5.cpp
// Provided File: MovieTree.hpp
// Instructor: Elizabeth Boese
// Description: Builds a binary search tree
// searches, traverses & deletes nodes in tree
// ===========================================

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "MovieTree.hpp"
#include "MovieTree.cpp"

using namespace std;

void menuDisplay();
void buildTree();
MovieTree* movieList = new MovieTree;

int main()
{	
	buildTree(); //calls function to build initial tree
	string menuChoice;
	menuDisplay(); //call function to display menu
	getline(cin, menuChoice);

	while (menuChoice != "6") //not quit
	{
		cout << "   " << endl;
		
		if (menuChoice == "1") //calls from MovieTree.cpp to search for movie title
		{
			string movieSearch;
			cout << "Enter the Title of the movie you would like to search: " ;
			getline (cin, movieSearch);
			movieList->findMovie(movieSearch);			
		}
		else if (menuChoice == "2") //calls from MovieTree.cpp to rent movie title
		{
			string movieRental;
			cout << "Enter the Title of the movie you would like to rent: " ;
			getline (cin, movieRental);
			movieList->rentMovie(movieRental);			
		}
		else if (menuChoice == "3") //calls from MovieTree.cpp to print inventory
		{
			movieList->printMovieInventory();
		}
		else if (menuChoice == "4") //counts movies in inventory
		{			
			int movies = movieList->countMovieNodes();
			cout << "   " << endl;
			cout << "There are " << movies << " movie titles in the inventory." << endl;
		}
		else if (menuChoice == "5") //deletes a movie from inventory
		{
			string movieDelete;
			cout << "Enter the Title of the movie you would like to delete: " ;
			getline (cin, movieDelete);
			movieList->deleteMovieNode(movieDelete);			
		}
		else if (menuChoice == "6") //quits program
		{
			cout << "Goodbye!" << endl;
		}
		else
		{
			cout << "Not a valid choice. Try again." << endl;
		}
		menuDisplay();
		getline(cin, menuChoice);
	}
	
	delete movieList;
	return 0;
}

/*
 * Function name: menuDisplay
 * Purpose: prints menu selections
 * @return - none
*/
void menuDisplay()
{
	cout << "     " << endl;
	cout << "Select a numerical option:" << endl;
	cout << "======Main Menu=====" << endl;
	cout << "1. Find a movie" << endl;
	cout << "2. Rent a movie" << endl;
	cout << "3. Print the inventory" << endl;
	cout << "4. Count movie inventory" << endl;
	cout << "5. Delete a movie" << endl;
	cout << "6. Quit" << endl;
}

/*
 * Function name: buildTree
 * Purpose: reads in text file & builds tree
 * @return - none
*/
void buildTree()
{
	string line;
	string txtRank;
	int ranking;
	string title;
	string txtYear;
	int year;
	string txtQuant;
	int quantity;
	
	ifstream inFile;
	inFile.open("HW4-Movies.txt");
	
	if (inFile)
	{		
		while (getline(inFile, line))
		{
			stringstream inFile(line);
			getline(inFile, txtRank, ','); //breaks line at the comma
			getline(inFile, title, ','); 
			getline(inFile, txtYear, ',');
			getline(inFile, txtQuant, '\n');
		
			ranking = atoi(txtRank.c_str());
			year = atoi(txtYear.c_str());
			quantity = atoi(txtQuant.c_str());
			
			movieList->addMovieNode(ranking, title, year, quantity);
		}
	}
	else
	{
		cout << "Text file did not open!" << endl;
	}
	inFile.close();
}
	
