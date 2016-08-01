#include "stdafx.h"
#include "UserManager.h"
#include <iostream>
#include <fstream>

static const std::string filename = "users.txt";

// unused methods
UserManager::UserManager() {}
UserManager::~UserManager() {}

void UserManager::login(char* username) {
	std::ifstream ifs(filename);

	User t_user;
	while (ifs.read(reinterpret_cast<char *>(&t_user), sizeof(t_user))) {
		if (strcmp(username, t_user.username) == 0) {
			currentUser = t_user;
			break;
		}
	}

	if (strcmp(currentUser.username, "DoesntExist") == 0) {
		currentUser = User{ };
		strcpy(currentUser.username, username);
	}

	ifs.close();
}

void UserManager::updateUserList() {
	const std::string tempFilename = "t_" + filename;

	std::ifstream ifs(filename);
	std::ofstream ofs(tempFilename);

	User t_user;
	while (ifs.read(reinterpret_cast<char *>(&t_user), sizeof(t_user))) {
		if (currentUser.saved && !currentUser.deleted && strcmp(currentUser.username, t_user.username) == 0) {
			ofs.write(reinterpret_cast<char *>(&currentUser), sizeof(currentUser));
		}
		else {
			ofs.write(reinterpret_cast<char *>(&t_user), sizeof(t_user));
		}
	}
	if (!currentUser.saved) {
		currentUser.saved = true;
		ofs.write(reinterpret_cast<char *>(&currentUser), sizeof(currentUser));
	}

	ifs.close();
	ofs.close();

	if (remove(filename.c_str())) { // delete the existing file
		std::cout << "Error deleteing old file of users..." << std::endl;
	}
	if (rename(tempFilename.c_str(), filename.c_str())) { // rename temp file to current
		std::cout << "Error renaming temp file to current... " << std::endl;
	}
}

void UserManager::updateUserInfo(int age, char gender, char* country) {
	currentUser.age = age;
	currentUser.gender = gender;
	//currentUser.country = country;
	strcpy(currentUser.country, country);
}

void UserManager::printUserMenu() {
	// we can through in some logic later to detect if user already has a record
	std::cout << "Score Manager Main Menu" << std::endl
		<< "[1] Create an Record" << std::endl
		<< "[2] Update a Score" << std::endl
		<< "[3] View Top 10" << std::endl
		<< "[4] View User Info" << std::endl
		<< "[5] Update User Info" << std::endl
		<< "[6] Delete This User" << std::endl
		<< "[7] Exit" << std::endl << std::endl
		<< "Your Option: ";
}

void UserManager::printUserInfo() {
	std::cout << "-------- User info -------" << std::endl
		<< "Username: " << currentUser.username << std::endl
		<< "Age:      " << currentUser.age << std::endl
		<< "Gender:   " << currentUser.gender << std::endl
		<< "Country:  " << currentUser.country << std::endl << std::endl;
}

bool UserManager::userExists() {
	return currentUser.saved;
}

void UserManager::deleteUser() {
	currentUser.deleted = true;
	updateUserList();
}
