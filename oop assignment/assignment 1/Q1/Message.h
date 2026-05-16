#pragma once
#include <iostream>
#include <string>
using namespace std;

class Message
{
    const int messageID;
    const string senderName;
    const string receiverName;
    string content;
    bool isRead;
    string timestamp;
    int relatedVehicleID;

    static int messageCount;

public:
    Message() : messageID(++messageCount), senderName("Unknown"),
                receiverName("Unknown"), content(""),
                isRead(false), timestamp("N/A"), relatedVehicleID(-1) {}

    Message(string sender, string receiver, string msg, string time, int vehicleID = -1) : messageID(++messageCount), senderName(sender), receiverName(receiver),
                                                                                           content(msg), isRead(false), timestamp(time), relatedVehicleID(vehicleID) {}

    Message(const Message &other) : messageID(++messageCount), senderName(other.senderName),
                                    receiverName(other.receiverName), content(other.content),
                                    isRead(other.isRead), timestamp(other.timestamp),
                                    relatedVehicleID(other.relatedVehicleID) {}

    int getMessageID() const { return messageID; }
    string getSenderName() const { return senderName; }
    string getReceiverName() const { return receiverName; }
    string getContent() const { return content; }
    bool getIsRead() const { return isRead; }
    string getTimestamp() const { return timestamp; }
    int getRelatedVehicleID() const { return relatedVehicleID; }

    void setIsRead(bool read) { isRead = read; }
    void setContent(const string &msg) { content = msg; }

    static int getMessageCount() { return messageCount; }

    void display() const
    {
        cout << "  [MSG #" << messageID << "] From: " << senderName
             << " -> To: " << receiverName << "\n"
             << "  Time   : " << timestamp << "\n"
             << "  Message: " << content << "\n"
             << "  Read   : " << (isRead ? "Yes" : "No") << "\n";
        if (relatedVehicleID != -1)
            cout << "  About Vehicle ID: " << relatedVehicleID << "\n";
    }

    void markAsRead() { isRead = true; }

    bool isFromSender(const string &name) const
    {
        return senderName == name;
    }

    bool isToReceiver(const string &name) const
    {
        return receiverName == name;
    }
};

int Message::messageCount = 0;