// Cpp-Assignment2.cpp : Defines the entry point for the console application.
//
#pragma warning(disable : 4996)
#include "stdafx.h"
#include "HighScoreManager.h"
#include <iostream>

using namespace std;

int main()
{
	string username;
	//login logic comes here and replace with the code below.
	cout << "Please enter your username: ";
	getline(cin, username);
	//I think we can check the length of username when they are loggin in.
	//date will always have the same format and automatically generated.

	bool scoreMenu = true;
	do {
		int scoreMenuOption;
		cout << "\nScore Manager Main Menu" << endl << "[1] Create an Record\n[2] Update a Score\n[3] View Top 10\n[4] Exit\n" << endl 
			 << "Your Option: ";
		cin >> scoreMenuOption;

		switch (scoreMenuOption) {
		case 1: {
			double score;
			cout << "\nPlease enter your score: ";
			cin >> score;
			cin.get();

			//create a scoremanager object
			HighScoreManager *userScore = new HighScoreManager(username, score);
			userScore->add(); //save the object in the file
			delete userScore; //delete memory

			scoreMenu = true;
			break;
		}
		case 2: {
			double score;
			cout << "\nPlease enter score to update: ";
			cin >> score;
			
			//save it in the file with updated score
			HighScoreManager *userScore = new HighScoreManager(username, score);
			userScore->update();
			delete userScore;

			scoreMenu = true;
			break;
		}
		case 3: {
			HighScoreManager *userScore = new HighScoreManager();//not initialising vector for now
			userScore->print();
			delete userScore;

			scoreMenu = true; //going back to score manager main menu
			break;
		}
		case 4:
			scoreMenu = false; //go back to program main menu
			break;
		default:
			cout << "Invalid Option. Please try again." << endl;
			scoreMenu = true;
			break;
		}
	} while (scoreMenu);
    return 0;
}