#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
using namespace std;

struct Messages {
    string sender;
    string receiver;
    string content;
    string timestamp;
    Messages() = default;
    Messages(string s, string r, string c, string t): sender(s), receiver(r), content(c), timestamp(t) {}
    friend ostream& operator<<(ostream& os, const Messages& msg) {
        os << " Sender : " << msg.sender << " Receiver : " << msg.receiver << " Content : " << msg.content << " Timestamp : " << msg.timestamp << endl;
        return os;
    }
};
struct Notification {
    string type;
    string fromUser;
    string toUser;
    string timestamp;
    string content;
    Notification() = default;
    Notification(string t, string f, string tu, string ti, string c): type(t), fromUser(f), toUser(tu), timestamp(ti), content(c) {}
    friend ostream& operator<<(ostream& os, const Notification& notification) {
        os << "Type : " << notification.type << " From : " << notification.fromUser << " To : " << notification.toUser << " Timestamp : " << notification.timestamp << " Content : " << notification.content << endl;
        return os;
    }
};
struct Post {
    string user;
    string content;
    string timestamp;
    string postID;
    string mediaURL;
    int likeCount = 0;
    string postType; 
    Post() = default;
    Post(string u, string c, string t, string pID, string mURL, int lCount,  string pType): user(u), content(c), timestamp(t), postID(pID), mediaURL(mURL), likeCount(lCount), postType(pType) {}
    void addLike() {
        likeCount++;
    }
    friend ostream& operator<<(ostream& os, const Post& post) {
        os << "User : " << post.user << " Timestamp : " << post.timestamp << " Content : " << post.content << " Likes : " << post.likeCount << " Type : " << post.postType << endl;
        return os;
    }
};

struct FriendRequest {
    string sender;
    string receiver;
    string timestamp;
    FriendRequest() = default;
    FriendRequest(string s, string r, string t) : sender(s), receiver(r), timestamp(t) {}
    friend ostream& operator<<(ostream& os, const FriendRequest& request) {
        os << "Sender : " << request.sender << " Receiver : " << request.receiver << " Timestamp : " << request.timestamp << endl;
        return os;
    }
};
struct userData {
    string username;
    string password;
    string name;
    string lastLogin;
    Stack<Post> *posts;
    Stack<Messages> *messages;
    Queue<Notification> *notifications;
    Queue<FriendRequest> *friendRequests;
    userData() : username(""), password(""), name(""), lastLogin("") {
        posts = new Stack<Post>();
        messages = new Stack<Messages>();
        notifications = new Queue<Notification>();
        friendRequests = new Queue<FriendRequest>();
    }
    userData(string u, string p, string n, string l) : username(u), password(p), name(n), lastLogin(l) {
        posts = new Stack<Post>();
        messages = new Stack<Messages>();
        notifications = new Queue<Notification>();
        friendRequests = new Queue<FriendRequest>();
    }
    friend ostream& operator<<(ostream& os, const userData& user) {
        os << user.username +"] : ";
        return os;
    }
};
struct edgeData {
    string from;
    string to;
    string relation;
    string status;
    edgeData() = default;
    edgeData(string f, string t, string r, string s): from(f), to(t), relation(r), status(s) {}
    friend ostream& operator<<(ostream& os, const edgeData& edge) {
        os <<edge.to;
        return os;
    }
};
struct Edge {
    edgeData data;
    Edge* next;
    Edge() : next(nullptr) {}
    Edge(edgeData e) : data(e), next(nullptr) {}
};
#endif // STRUCTURES_H
