#include "stdafx.h"
#include "UserManager.h"
#include <iostream>
#include <fstream>

static const std::string filename = "users.txt";

// allows the user to login via username
void UserManager::login(char* username) {
	std::ifstream ifs(filename);

	// find the user in the file
	User t_user;
	while (ifs.read(reinterpret_cast<char *>(&t_user), sizeof(t_user))) {
		if (strcmp(username, t_user.username) == 0) {
			currentUser = t_user;
			break;
		}
	}

	// detect new users
	if (strcmp(currentUser.username, "DoesntExist") == 0) {
		currentUser = User{ };
		strcpy(currentUser.username, username);
	}

	ifs.close();
}

// saves the user list to a file
void UserManager::updateUserList() {
	const std::string tempFilename = "t_" + filename;

	std::ifstream ifs(filename);
	std::ofstream ofs(tempFilename);

	// start storing everything from the old file into the temp file and find and replace the currentUser
	User t_user;
	while (ifs.read(reinterpret_cast<char *>(&t_user), sizeof(t_user))) {
		if (t_user.deleted) continue;
		if (currentUser.saved && strcmp(currentUser.username, t_user.username) == 0) {
			ofs.write(reinterpret_cast<char *>(&currentUser), sizeof(currentUser));
		}
		else {
			ofs.write(reinterpret_cast<char *>(&t_user), sizeof(t_user));
		}
	}

	// append to the file if the user is new
	if (!currentUser.saved) {
		currentUser.saved = true;
		ofs.write(reinterpret_cast<char *>(&currentUser), sizeof(currentUser));
	}

	ifs.close();
	ofs.close();

	// delete the old file rename the temp
	if (remove(filename.c_str())) { // delete the existing file
		std::cout << "Error deleteing old file of users..." << std::endl;
	}
	if (rename(tempFilename.c_str(), filename.c_str())) { // rename temp file to current
		std::cout << "Error renaming temp file to current... " << std::endl;
	}
}

// allows you to change the user's information
void UserManager::updateUserInfo(int age, char gender, char* country) {
	currentUser.age = age;
	currentUser.gender = gender;
	//currentUser.country = country;
	strcpy(currentUser.country, country);
}

// print out the menu the user interacts with
void UserManager::printUserMenu() {
	// we can through in some logic later to detect if user already has a record
	std::cout << "Score Manager Main Menu" << std::endl
		<< "[1] Set/Update your score" << std::endl
		<< "[2] View Top 10" << std::endl
		<< "[3] View User Info" << std::endl
		<< "[4] Update User Info" << std::endl
		<< "[5] Delete This User" << std::endl
		<< "[6] Exit" << std::endl << std::endl
		<< "Your Option: ";
}

// print out the user's information
void UserManager::printUserInfo() {
	std::cout << "-------- User info -------" << std::endl
		<< "Username: " << currentUser.username << std::endl
		<< "Age:      " << currentUser.age << std::endl
		<< "Gender:   " << currentUser.gender << std::endl
		<< "Country:  " << currentUser.country << std::endl << std::endl;
}

// returns whether the user exists or is new
bool UserManager::userExists() {
	return currentUser.saved;
}

// sets the user up to be delete from the file
void UserManager::deleteUser() {
	currentUser.deleted = true;
	updateUserList();
}
