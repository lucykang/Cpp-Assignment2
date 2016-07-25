#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

using namespace std;

class HighScoreManager {
private:
	struct UserScore {
		char username[20];
		double score;
		char date[25];
	};
	UserScore newUserScore;
	vector<UserScore> scoreList;
	const string SCORE_FILE = "highScore.dat";

public:
	HighScoreManager();
	HighScoreManager(string, double);
	~HighScoreManager();
	void add();
	void update();
	bool remove();
	void print();
	void save();
	void sortVector();
	void initialiseVector();
	string setTime();
};

//constructors
HighScoreManager::HighScoreManager() {
	//initialise vector from the file when an object is created
	initialiseVector();
}

HighScoreManager::HighScoreManager(string username, double score) {
	initialiseVector();	
	string date = setTime();

	strcpy(newUserScore.username, username.c_str());
	newUserScore.score = score;
	strcpy(newUserScore.date, date.c_str());
}

//destructor
HighScoreManager::~HighScoreManager() {}

void HighScoreManager::add() {
	scoreList.push_back(newUserScore);
	sortVector();
	save();
}

void HighScoreManager::update() {


	//testing username and vector
	cout << "testing username: " << newUserScore.username << endl;
	cout << "testing vector before update" << endl;
	for (int i = 0; i < scoreList.size(); i++) {
		cout << scoreList[i].username << scoreList[i].score << endl;
	}



	int index = 0;
	if (remove() == true) {
		add(); //add to the vector and save it
		cout << "\nScore is updated." << endl;
	}
	else {
		cout << "\nNo username was found. Please enter new record." << endl;
	}
}

bool HighScoreManager::remove() {
	for (int i = 0; i < scoreList.size(); i++) {
		if (scoreList[i].username == newUserScore.username) {
			scoreList.erase(scoreList.begin() + i);
			return true;
			break;
		}
	}
	return false;
}

void HighScoreManager::print() {
	ifstream inScoreFile(SCORE_FILE); //read from file
	if (!inScoreFile.is_open()) {
		cout << "\nUnable to open score file.";
		cin.get();
	}
	else {
		UserScore tempUser;
		int index = 0;
		cout << "\nDisplaying Top 10 Records" << endl;
		cout << setw(15) << "Username" << setw(10) << "Score" << setw(30) << "Date" << endl;
		while (inScoreFile.read(reinterpret_cast<char *>(&tempUser), sizeof(tempUser)) && index < 10) {
			cout << setw(15) << tempUser.username
				<< setw(10) << tempUser.score
				<< setw(30) << tempUser.date << endl;
		}
	}
	inScoreFile.close();
}

void HighScoreManager::save() {
	ofstream outScoreFile(SCORE_FILE, ios::trunc, ios::binary);

	if (!outScoreFile.is_open())
	{
		std::cout << "\nUnable to open file." << endl;
		std::cin.get();
		//exit(1);
	}
	else {
		for (int i = 0; i < scoreList.size(); i++) {
			outScoreFile.write(reinterpret_cast<char *>(&scoreList[i]), sizeof(scoreList[i]));
		}
		outScoreFile.close();
	}
}

void HighScoreManager::initialiseVector() {
	//initialise vector from the file when an object is created
	ifstream inScoreFile(SCORE_FILE); //read from file

	if (!inScoreFile.is_open()) {
		cout << "\nUnable to open score file.";
		cin.get();
	}
	else {
		UserScore tempUser;
		while (inScoreFile.read(reinterpret_cast<char *>(&tempUser), sizeof(tempUser))) {
			scoreList.push_back(tempUser);
		}
	}
	inScoreFile.close();
}

void HighScoreManager::sortVector()
{
	int startScan, maxIndex, size;
	UserScore maxScore;

	size = scoreList.size();
	for (startScan = 0; startScan < (size - 1); startScan++)
	{
		maxIndex = startScan;
		maxScore = scoreList[startScan];

		for (int index = startScan + 1; index < size; index++)
		{
			if (scoreList[index].score > maxScore.score)
			{
				maxScore = scoreList[index];
				maxIndex = index;
			}
		}
		scoreList[maxIndex] = scoreList[startScan];
		scoreList[startScan] = maxScore;
	}
}

string HighScoreManager::setTime() {
	//initialise date when user entered into score manager main menu
	time_t rawtime;
	struct tm * timeinfo = nullptr;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%y %I:%M:%S", timeinfo);
	return buffer;
}