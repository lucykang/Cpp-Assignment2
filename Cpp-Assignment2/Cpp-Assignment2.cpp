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
	//getline(cin, username);
	//I think we can check the length of username when they are loggin in.
	//date will always have the same format and automatically generated.

	userManager.login(username);
	
	if (userManager.userExists()) {
		std::cout << "Welcome back " << username << std::endl;
	}
	else {
		std::cout << "It's nice to meet you " << username << std::endl;
		userManager.updateUserList(); // save the new user
	}

	bool scoreMenu = true;
	do {
		int scoreMenuOption;

		userManager.printUserMenu();
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
			userManager.printUserInfo();
			break;
		case 5: {
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
		case 6:
			userManager.deleteUser();
			userManager.updateUserList();

			std::cout << "Your account has been deleted! Bye bye!" << std::endl;

			scoreMenu = false;
			break;
		case 7:
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