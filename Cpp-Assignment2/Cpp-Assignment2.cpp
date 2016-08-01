// Cpp-Assignment2.cpp : Defines the entry point for the console application.
//
#pragma warning(disable : 4996)
#include "stdafx.h"
#include "HighScoreManager.h"
#include "UserManager.h"
#include <iostream>

using namespace std;

int main() {
	UserManager userManager;
	char username[20];

	//login logic comes here and replace with the code below.
	cout << "Please enter your username: ";
	cin >> username; cin.ignore();

	// log the user in and display their welcome message
	userManager.login(username);
	
	if (userManager.userExists()) {
		std::cout << "Welcome back " << username << std::endl;
	}
	else {
		std::cout << "It's nice to meet you " << username << std::endl;
		userManager.updateUserList(); // save the new user
	}

	// display menu while scoreMenu is true
	bool scoreMenu = true;
	do {
		int scoreMenuOption;

		userManager.printUserMenu();
		cin >> scoreMenuOption;

		switch (scoreMenuOption) {
		// if the user wants to set their score
		case 1: {
			double score;
			cout << "\nPlease enter your score: ";
			cin >> score; cin.ignore();

			//create a scoremanager object
			HighScoreManager *userScore = new HighScoreManager(username, score);
			userScore->setScore(); //save the object in the file
			delete userScore; //delete memory

			scoreMenu = true;
			break;
		}
		// prints out the top 10 users scores
		case 2: {
			HighScoreManager *userScore = new HighScoreManager();//not initialising vector for now
			userScore->print();
			delete userScore;

			scoreMenu = true; //going back to score manager main menu
			break;
		}
		// displays the user's information to the screen
		case 3:
			userManager.printUserInfo();
			break;
		// updates the user's information
		case 4: {
			int age;
			std::cout << "Enter your new Age: ";
			cin >> age; cin.ignore();

			char gender;
			std::cout << "Enter your Gender (M/F): ";
			cin >> gender; cin.ignore();

			char country[20];
			std::cout << "Enter your Country: ";
			cin >> country; cin.ignore();

			userManager.updateUserInfo(age, gender, country);
			userManager.updateUserList(); // save the changes

			break;
		}
		// Deletes the users account 
		case 5:
			userManager.deleteUser();
			userManager.updateUserList();

			std::cout << "Your account has been deleted! Bye bye!" << std::endl;

			scoreMenu = false; // exit out of the menu
			break;
		case 6:
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