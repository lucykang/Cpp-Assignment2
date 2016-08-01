#pragma once
class UserManager {
private:
	struct User {
		char username[20];
		int age;
		char gender;
		char country[20];
		bool saved;
		bool deleted;
	};
	User currentUser{ "DoesntExist" };
public:
	void login(char *);
	void updateUserList();
	void updateUserInfo(int age, char gender, char* country);
	void printUserMenu();
	void printUserInfo();
	bool userExists();
	void deleteUser();
	//void setHighScore(double score);
};

