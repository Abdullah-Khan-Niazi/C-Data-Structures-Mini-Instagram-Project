#include"Graph.h"
#include"UI.h"
#include <iostream>
#include <iomanip>
#include<string>
#include <ctime>
#include<fstream>
#include<conio.h>
using namespace std;

class Instagram :public UI {
private:
	AdjList* insta;
	bool isUsernameUnique(const string& username);
	void Return();
	void changePassword(AdjNode* obj, bool admin = true);
    void viewFollowersList(AdjNode* obj);
public:
	void printAvailableUsers();
	Instagram();
	~Instagram();
	void destroyAndCreate();
	string getCurrentTimeAndDate();
	void loggedIn(AdjNode*& obj, bool admin = false);
	void SignUp();
	void SignIn();
	void AdminMode();

	void viewFeed(AdjNode*& obj);
	void viewMessages(AdjNode*& obj);
	void viewNotification(AdjNode*& obj);
	void viewFriendRequest(AdjNode*& obj);
	void sendMessages(AdjNode*& obj);
	void sendFriendRequest(AdjNode*& obj);
private:
	void approveAllRequests(AdjNode*& obj);
	void removeRequest(AdjNode*& obj, string from);
public:
	void acceptFriendRequest(AdjNode*& obj);
private:
	void ExportMessageToFile(AdjNode*& obj, ofstream& messages);
	void ExportNotificationsToFile(AdjNode*& obj, ofstream& notifications);
	void ExportPostsToFile(AdjNode*& obj, ofstream& posts);
	void ExportFriendRequestsToFile(AdjNode*& obj, ofstream& friendRequests);
	void ExportEdgesToFile(AdjNode*& obj, ofstream& edges);
public:
	void ExportToFile();
private:
	void importMessagesFromFile(AdjNode*& temp, ifstream& messages);
	void importNotificationsFromFile(AdjNode*& temp, ifstream& notifications);
	void importPostsFromFile(AdjNode*& temp, ifstream& posts);
	void importFriendRequestsFromFile(AdjNode*& temp, ifstream& friendRequests);
	void importEdgesFromFile(AdjNode*& temp, ifstream& edges);
public:
	void importFromFile();
	void print();
	void mainMenu();
};
#pragma once
