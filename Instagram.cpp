#include"Instagram.h"
using namespace std;


bool Instagram::isUsernameUnique(const string& username) {
	if (insta->findVertex(username) == nullptr) {
		return true;
	}
	return false;
}
void Instagram::Return() {
	printBoxed("Press Any [Key] to Return");
	while (!_kbhit()) {}
	char ch = _getch();
	clear();
	printBoxed("Returning to Main Menu...");
	delay(1500);
}
void Instagram::changePassword(AdjNode* obj, bool admin) {
	clear();
	printTitle("CHANGE PASSWORD");
	string password;
	if (admin == false) {
		cout << "Enter Old Password : "; cin >> password;
		if (obj->data.password == password) {
			cout << "Enter New Password : "; cin >> password;
			obj->data.password = password;
		}
		else {
			printBoxed("Incorrect Password");
			Return();
		}
	}
	else {
		cout << "Enter New Password : "; cin >> password;
		obj->data.password = password;
	}
	clear();
	printBoxed("Password Changed Successfully");
	delay(1500);
}
void Instagram::viewFollowersList(AdjNode* obj) {
	clear();
	printTitle("FOLLOWERS/FRIENDS");
	obj->edges->print();
	printSeparator('=');
	Return();
}

void Instagram::printAvailableUsers() {
	insta->printNames();
	printSeparator('=');
}
Instagram::Instagram() {
	insta = new AdjList;
}
Instagram::~Instagram() {
	delete insta;
}
void Instagram::destroyAndCreate() {
	delete insta;
	insta = new AdjList;
}
string Instagram::getCurrentTimeAndDate() {
	time_t now = time(nullptr);
	tm localTime = {};
	localtime_s(&localTime, &now);
	char dateTime[20];
	strftime(dateTime, sizeof(dateTime), "%Y-%m-%d %H:%M:%S", &localTime);
	string str(dateTime);
	return str;
}
void Instagram::loggedIn(AdjNode*& obj, bool admin) {
	if (!obj) {
		printBoxed("Error : Invalid User Node.");
		return;
	}
	char choice = ' ';
	while (choice != 27) {
		clear();
		printTitle("Logged-In as " + obj->data.name);
		printBoxed("========== MENU ==========");
		printCentered("[1] View Feed");
		printCentered("[2] View Messages");
		printCentered("[3] Send Message");
		printCentered("[4] View Friend Requests");
		printCentered("[5] Send Friend Request");
		printCentered("[6] View Notifications");
		printCentered("[7] Accept/Reject Friend Request");
		printCentered("[8] View Followers List");
		printCentered("[9] Change Password");
		printCentered("[Esc] Logout");
		printSeparator('=');
		choice = _getch();
		switch (choice) {
		case '1':
			clear();
			viewFeed(obj);
			break;
		case '2':
			clear();
			viewMessages(obj);
			break;
		case '3':
			clear();
			sendMessages(obj);
			break;
		case '4':
			clear();
			viewFriendRequest(obj);
			break;
		case '5':
			clear();
			sendFriendRequest(obj);
			break;
		case '6':
			clear();
			viewNotification(obj);
			break;
		case '7':
			clear();
			acceptFriendRequest(obj);
			break;
		case '8':
			viewFollowersList(obj);
			break;
		case '9':
			changePassword(obj, admin);
			break;
		case 27:
			clear();
			printBoxed("Logged out successfully!");
			break;
		default:
			clear();
			printBoxed("Invalid choice. Please try again.");
			delay(1500);
		}
	}
}

void  Instagram::SignUp() {
	printTitle("SIGN UP");
	string username, password, name;
	cout << "Enter Name : "; cin >> name;
	cout << "Enter Username : "; cin >> username;
	if (!isUsernameUnique(username)) {
		printBoxed("Username already exists.Try another one.");
		Return();
		return;
	}
	cout << "Create a Password : "; cin >> password;
	string timestamp = getCurrentTimeAndDate();
	timestamp[10] = '_';
	userData temp(username, password, name, timestamp);
	insta->insertVertex(temp);
	printBoxed("Signed-Up Successfully");
	delay(1500);
}
void  Instagram::SignIn() {
	printTitle("SIGN IN");
	string username;
	string password;
	cout << "Enter UserName : "; cin >> username;
	AdjNode* temp = insta->findVertex(username);
	if (!temp) {
		printBoxed("Error: Username not found.");
		Return();
		return;
	}
	if (temp->data.username == username) {
		cout << "Enter Password : "; cin >> password;
		if (password == temp->data.password) {
			printBoxed("Logged-In Successfully");
			string timestamp = getCurrentTimeAndDate();
			timestamp[10] = '_';
			delay(1000);
			loggedIn(temp);
			temp->data.lastLogin = timestamp;
		}
		else {
			printBoxed("Error : Incorrect Password.");
			Return();
			return;
		}
	}
}
void  Instagram::AdminMode() {
	int id = 0;
	string username = "";
	cout << "Enter Password : "; cin >> username;
	if (username == "MAYDAY" || username == "mayday") {
		clear();
	}
	else {
		return;
	}
	AdjNode* temp = nullptr;
	while (true) {
		clear();
		printTitle("ADMIN MODE");
		cout << "Available Users:" << endl;
		printAvailableUsers();
		cout << "Select User by : [1] Username | [2] ID | [Esc] Main Menu" << endl;
		char ch = _getch();
		if (ch == '1') {
			cout << "Enter Username : "; cin >> username;
			temp = insta->findVertex(username);
			if (temp != nullptr) {
				loggedIn(temp, true);
			}
			else {
				clear();
				printBoxed("Username not found. Try again.");
				delay(1500);
				clear();
			}
		}
		else if (ch == '2') {
			cout << "Enter ID : "; cin >> id;
			temp = insta->findVertex(id);
			if (temp != nullptr) {
				loggedIn(temp, true);
			}
			else {
				clear();
				printBoxed("ID not found. Try again.");
				delay(1500);
				clear();
			}
		}
		else if (ch == 27) {
			clear();
			printBoxed("Returning to Main Menu");
			delay(1500);
			return;
		}
		else {
			clear();
			printBoxed("Invalid Input. Please press [1] for Username or [2] for ID.");
			delay(1500);
			clear();
		}
	}
}

void  Instagram::viewFeed(AdjNode*& obj) {
	printTitle("FEED");
	if (obj->data.posts->isEmpty()) {
		printBoxed("No Posts Available Currently");
		Return();
		return;
	}
	obj->data.posts->print();
	printSeparator('=');
	Return();
}
void  Instagram::viewMessages(AdjNode*& obj) {
	printTitle("MESSAGES");
	Stack<Messages>* msg = obj->data.messages->copy();
	if (msg->isEmpty()) {
		printBoxed("No Messages Available Currently");
		Return();
		return;
	}
	while (msg->isEmpty() != true) {
		cout << msg->pop();
	}
	printSeparator('=');
	Return();
}
void  Instagram::viewNotification(AdjNode*& obj) {
	printTitle("NOTIFICATIONS");
	Queue<Notification>* received = obj->data.notifications->copy();
	if (received->isEmpty()) {
		printBoxed("No Notifications Available Currently");
		Return();
		return;
	}
	while (received->isEmpty() != true) {
		cout << received->dequeue();
	}
	printSeparator('=');
	Return();
}
void  Instagram::viewFriendRequest(AdjNode*& obj) {
	printTitle("FRIEND REQUESTS");
	Queue<FriendRequest>* received = obj->data.friendRequests->copy();
	if (received->isEmpty()) {
		printBoxed("No Friend Request Available Currently");
		Return();
		return;
	}
	while (received->isEmpty() != true) {
		cout << received->dequeue();
	}
	printSeparator('=');
	Return();
}
void  Instagram::sendMessages(AdjNode*& obj) {
	printTitle("SEND A MESSAGE");
	string sender;
	string receiver;
	string content;
	string timestamp;
	cout << "Enter Receiver User Name : "; cin >> receiver;
	cout << "Enter Message to Send : "; cin >> content;
	if (insta->findVertex(receiver) == nullptr) {
		printBoxed("A User with Username " + receiver + " is Not Available");
		Return();
		return;
	}
	timestamp = getCurrentTimeAndDate();
	timestamp[10] = '_';
	sender = obj->data.username;
	Messages msg(sender, receiver, content, timestamp);
	obj->data.messages->push(msg);
	Notification notification("Message_Received", sender, receiver, timestamp, obj->data.name + "_Sent_a_Message");
	Notification notification2("Message_Sent", "Instagram", sender, timestamp, "Message_Sent_Successfully_to_" + insta->findVertex(receiver)->data.name);
	obj->data.notifications->enqueue(notification2);
	insta->findVertex(receiver)->data.notifications->enqueue(notification);
	printBoxed("Message Sent Successfully");
	delay(1500);
}
void  Instagram::sendFriendRequest(AdjNode*& obj) {
	printTitle("SEND A FRIEND REQUEST");
	string sender;
	string receiver;
	string timestamp;
	cout << "Enter Receiver User Name : "; cin >> receiver;
	if (insta->findVertex(receiver) == nullptr) {
		printBoxed("A User with Username " + receiver + " is Not Available");
		Return();
		return;
	}
	sender = obj->data.username;
	timestamp = getCurrentTimeAndDate();
	timestamp[10] = '_';
	FriendRequest request(sender, receiver, timestamp);
	insta->findVertex(receiver)->data.friendRequests->enqueue(request);
	Notification notification("Friend_Request_Received", sender, receiver, timestamp, obj->data.name + "_Sent_a_Friend_Request");
	Notification notification2("Friend_Request_Sent", "Instagram", obj->data.username, timestamp, "Friend_Request_Sent_Successfully_to_" + insta->findVertex(receiver)->data.name);
	obj->data.notifications->enqueue(notification2);
	insta->findVertex(receiver)->data.notifications->enqueue(notification);
	printBoxed("Request Sent Successfully");
	delay(1500);
}

void  Instagram::approveAllRequests(AdjNode*& obj) {
	while (!obj->data.friendRequests->isEmpty()) {
		FriendRequest request = obj->data.friendRequests->dequeue();
		string name = request.sender;
		string timestamp = getCurrentTimeAndDate();
		timestamp[10] = '_';
		edgeData temp(obj->data.username, name, "Friends", "Active");
		obj->edges->insert_at_end(temp);
		temp = edgeData(name, obj->data.username, "Friends", "Active");
		insta->findVertex(name)->edges->insert_at_end(temp);
		Notification notification("Friend_Request_Accepted", "Instagram", name, timestamp, "Your_Friend_Request_Was_Accepted_By_" + obj->data.name);
		Notification notification2("Friend_Request_Accepted", "Instagram", obj->data.username, timestamp, "You_Have_Accepted_The_Friend_Request_From_" + insta->findVertex(name)->data.name);
		obj->data.notifications->enqueue(notification2);
		insta->findVertex(name)->data.notifications->enqueue(notification);
		removeRequest(obj, name);
		printBoxed("Request Accepted Successfully");
		delay(1500);
	}
}
void  Instagram::removeRequest(AdjNode*& obj, string from) {
	Queue<FriendRequest>* requests = obj->data.friendRequests->copy();
	obj->data.friendRequests->makeNull();
	while (!requests->isEmpty()) {
		FriendRequest request = requests->dequeue();
		if (request.sender != from) {
			obj->data.friendRequests->enqueue(request);
		}
	}
}

void  Instagram::acceptFriendRequest(AdjNode*& obj) {
	printTitle("ACCEPT FRIEND REQUEST");
	if (obj->data.friendRequests->isEmpty()) {
		printBoxed("No Friend Requests Available");
		return;
	}
	cout << "Friend Requests : " << endl;
	Queue<FriendRequest>* received = obj->data.friendRequests->copy();
	while (!received->isEmpty()) {
		cout << received->dequeue();
	}
	printSeparator('=');
	string name;
	cout << "Enter The Username of The Request to Process : "; cin >> name;
	if (isUsernameUnique(name) == false) {
		char choice;
		cout << "Do You Want To Accept The Request (Yes : Y/No : N) : "; cin >> choice;
		string timestamp = getCurrentTimeAndDate();
		timestamp[10] = '_';
		if (choice == 'y' || choice == 'Y') {
			edgeData temp(obj->data.username, name, "Friends", "Active");
			obj->edges->insert_at_end(temp);
			temp = edgeData(name, obj->data.username, "Friends", "Active");
			insta->findVertex(name)->edges->insert_at_end(temp);
			Notification notification("Friend_Request_Accepted", "Instagram", name, timestamp, "Your_Friend_Request_Was_Accepted_By_" + obj->data.name);
			Notification notification2("Friend_Request_Accepted", "Instagram", obj->data.username, timestamp, "You_Have_Accepted_The_Friend_Request_From_" + insta->findVertex(name)->data.name);
			obj->data.notifications->enqueue(notification2);
			insta->findVertex(name)->data.notifications->enqueue(notification);
			removeRequest(obj, name);
			printBoxed("Request Accepted Successfully");
		}
		else if (choice == 'n' || choice == 'N') {
			Notification notification("Friend_Request_Rejected", "Instagram", name, timestamp, "Your_Friend_Request_Was_Rejected_By_" + obj->data.username);
			Notification notification2("Friend_Request_Rejected", "Instagram", obj->data.username, timestamp, "You_Have_Rejected_The_Friend_Request_From_" + insta->findVertex(name)->data.name);
			insta->findVertex(name)->data.notifications->enqueue(notification);
			obj->data.notifications->enqueue(notification2);
			removeRequest(obj, name);
			printBoxed("Request Rejected Successfully");
		}
	}
	delay(1500);
}

void  Instagram::ExportMessageToFile(AdjNode*& obj, ofstream& messages) {
	Messages msg;
	while (!obj->data.messages->isEmpty()) {
		msg = obj->data.messages->pop();
		messages << msg.sender << " " + msg.receiver << " " + msg.content << " " << msg.timestamp << endl;
	}
}
void  Instagram::ExportNotificationsToFile(AdjNode*& obj, ofstream& notifications) {
	Notification notification;
	while (!obj->data.notifications->isEmpty()) {
		notification = obj->data.notifications->dequeue();
		notifications << notification.type << " " + notification.fromUser << " " + notification.toUser << " " + notification.timestamp << " " + notification.content << endl;
	}
}
void  Instagram::ExportPostsToFile(AdjNode*& obj, ofstream& posts) {
	Post post;
	while (!obj->data.posts->isEmpty()) {
		post = obj->data.posts->pop();
		posts << post.user << " " + post.content << " " + post.timestamp << " " + post.postID << " " + post.mediaURL << " " + post.likeCount << " " + post.postType << endl;
	}
}
void Instagram::ExportFriendRequestsToFile(AdjNode*& obj, ofstream& friendRequests) {
	Queue<FriendRequest>* requests = obj->data.friendRequests->copy();
	while (!requests->isEmpty()) {
		FriendRequest request = requests->dequeue();
		friendRequests << request.sender << " " << request.receiver << " " << request.timestamp << endl;
	}
}
void  Instagram::ExportEdgesToFile(AdjNode*& obj, ofstream& edges) {
	Edge* edge = obj->edges->getHead();
	while (edge != nullptr) {
		edges << edge->data.from << " " << edge->data.to << " " << edge->data.relation << " " << edge->data.status << endl;
		edge = edge->next;
	}
}


void Instagram::ExportToFile() {
	ofstream user;
	ofstream posts;
	ofstream messages;
	ofstream notifications;
	ofstream friendRequests;
	ofstream edges;
	user.open("users.txt");
	messages.open("messages.txt");
	notifications.open("notifications.txt");
	posts.open("posts1.txt");
	friendRequests.open("friendrequests.txt");
	edges.open("edges.txt");
	AdjNode* temp = insta->getFirstNode();
	while (temp != nullptr) {
		user << temp->data.username << " " + temp->data.password << " " + temp->data.name << " " + temp->data.lastLogin << endl;
		ExportMessageToFile(temp, messages);
		ExportNotificationsToFile(temp, notifications);
		ExportFriendRequestsToFile(temp, friendRequests);
		ExportEdgesToFile(temp, edges);
		temp = temp->next;
	}
	temp = insta->getFirstNode();
	ExportPostsToFile(temp, posts);
	user.close();
	posts.close();
	notifications.close();
	messages.close();
	friendRequests.close();
	edges.close();
}

void Instagram::importMessagesFromFile(AdjNode*& temp, ifstream& messages) {
	string sender;
	string receiver;
	string content;
	string timestamp;
	while (messages >> sender >> receiver >> content >> timestamp) {
		Messages msg(sender, receiver, content, timestamp);
		if (msg.receiver == temp->data.username) {
			temp->data.messages->push(msg);
		}
	}
}
void Instagram::importNotificationsFromFile(AdjNode*& temp, ifstream& notifications) {
	string type;
	string fromUser;
	string toUser;
	string content;
	string timestamp;
	while (notifications >> type >> fromUser >> toUser >> timestamp >> content) {
		Notification notification(type, fromUser, toUser, timestamp, content);
		if (notification.toUser == temp->data.username) {
			temp->data.notifications->enqueue(notification);
		}
	}
}
void Instagram::importPostsFromFile(AdjNode*& temp, ifstream& posts) {
	string User;
	string content;
	string timestamp;
	string postID;
	string mediaURL;
	string postType;
	int likeCount;
	while (posts >> User >> content >> timestamp >> postID >> mediaURL >> likeCount >> postType) {
		Post post(User, content, timestamp, postID, mediaURL, likeCount, postType);
		temp->data.posts->push(post);
	}
}
void Instagram::importFriendRequestsFromFile(AdjNode*& temp, ifstream& friendRequests) {
	string sender, receiver, timestamp;
	while (friendRequests >> sender >> receiver >> timestamp) {
		if (receiver == temp->data.username) {
			FriendRequest request(sender, receiver, timestamp);
			temp->data.friendRequests->enqueue(request);
		}
	}
}
void Instagram::importEdgesFromFile(AdjNode*& temp, ifstream& edges) {
	string from, to, relation, status;
	while (edges >> from >> to >> relation >> status) {
		if (from == temp->data.username) {
			edgeData edge(from, to, relation, status);
			temp->edges->insert_at_end(edge);
		}
	}
}


void Instagram::importFromFile() {
	ifstream user;
	ifstream posts;
	ifstream messages;
	ifstream notifications;
	ifstream friendRequests;
	ifstream edges;

	string username;
	string password;
	string name;
	string lastLogin;
	user.open("users.txt");
	while (user >> username >> password >> name >> lastLogin) {
		posts.open("posts.txt");
		notifications.open("notifications.txt");
		messages.open("messages.txt");
		friendRequests.open("friendrequests.txt");
		edges.open("edges.txt");
		userData obj(username, password, name, lastLogin);
		insta->insertVertex(obj);
		AdjNode* temp = insta->findVertex(username);
		importMessagesFromFile(temp, messages);
		importNotificationsFromFile(temp, notifications);
		importPostsFromFile(temp, posts);
		importFriendRequestsFromFile(temp, friendRequests);
		importEdgesFromFile(temp, edges);
		posts.close();
		notifications.close();
		messages.close();
		friendRequests.close();
		edges.close();
	}
	user.close();
}
void Instagram::print() {
	printTitle("GRAPH/AVL-BST/HASHMAP REPRESENTATION");
	insta->print();
	printSeparator('=');
	Return();
}
void Instagram::mainMenu() {
	char choice;
	while (true) {
		importFromFile();
		clear();
		printTitle("Welcome to Instagram Console App");
		printBoxed("========== MAIN MENU ==========");
		printCentered("[1] Sign Up");
		printCentered("[2] Sign In");
		printCentered("[3] Display Users");
		printCentered("[4] Admin Mode");
		printCentered("[Esc] Exit");
		printSeparator('=');
		choice = _getch();
		switch (choice) {
		case '1':
			clear();
			SignUp();
			break;
		case '2':
			clear();
			SignIn();
			break;
		case '3':
			clear();
			print();
			break;
		case '4':
			clear();
			AdminMode();
			break;
		case 27:
			clear();
			printBoxed("Exiting The Application. Goodbye!");
			return;
		default:
			clear();
			printBoxed("Invalid Choice. Please Try Again.");
			delay(1000);
		}
		ExportToFile();
		destroyAndCreate();
	}
}

