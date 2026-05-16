#pragma once
#include <iostream>
#include "Message.h"
using namespace std;

const int maxMessages = 200;

class Inbox
{
    Message *messages[maxMessages];
    int count;
    string ownerName;
    bool autoMarkRead;
    int unreadCount;

    static int totalInboxes;

public:
    Inbox() : count(0), ownerName("Unknown"), autoMarkRead(false), unreadCount(0)
    {
        for (int i = 0; i < maxMessages; i++)
            messages[i] = nullptr;
        totalInboxes++;
    }

    Inbox(const string &owner, bool autoRead = false) : count(0), ownerName(owner), autoMarkRead(autoRead), unreadCount(0)
    {
        for (int i = 0; i < maxMessages; i++)
            messages[i] = nullptr;
        totalInboxes++;
    }

    int getCount() const { return count; }
    string getOwnerName() const { return ownerName; }
    int getUnreadCount() const { return unreadCount; }
    static int getTotalInboxes() { return totalInboxes; }

    void setAutoMarkRead(bool a) { autoMarkRead = a; }

    void addMessage(const Message &msg)
    {
        if (count >= maxMessages)
        {
            cout << "Inbox full.\n";
            return;
        }
        messages[count++] = new Message(msg);
        unreadCount++;
    }

    void deleteMessage(int messageID)
    {
        for (int i = 0; i < count; i++)
        {
            if (messages[i] != nullptr && messages[i]->getMessageID() == messageID)
            {
                if (!messages[i]->getIsRead())
                    unreadCount--;
                delete messages[i];
                for (int j = i; j < count - 1; j++)
                    messages[j] = messages[j + 1];
                messages[--count] = nullptr;
                cout << "Message #" << messageID << " deleted.\n";
                return;
            }
        }
        cout << "Message #" << messageID << " not found.\n";
    }

    void markAllRead()
    {
        for (int i = 0; i < count; i++)
            if (messages[i] != nullptr && !messages[i]->getIsRead())
            {
                messages[i]->markAsRead();
            }
        unreadCount = 0;
    }

    void displayAll() const
    {
        cout << "\n── Inbox of " << ownerName
             << " (" << count << " messages, " << unreadCount << " unread) ──\n";
        for (int i = 0; i < count; i++)
            if (messages[i] != nullptr)
            {
                messages[i]->display();
                cout << "\n";
            }
    }

    void displayUnread() const
    {
        cout << "\n── Unread messages for " << ownerName << " ──\n";
        for (int i = 0; i < count; i++)
            if (messages[i] != nullptr && !messages[i]->getIsRead())
                messages[i]->display();
    }

    ~Inbox()
    {
        for (int i = 0; i < maxMessages; i++)
            if (messages[i] != nullptr)
            {
                delete messages[i];
                messages[i] = nullptr;
            }
    }
};
int Inbox::totalInboxes = 0;