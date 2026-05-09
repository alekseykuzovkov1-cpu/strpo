#ifndef NOTIFICATION_OOP_HPP
#define NOTIFICATION_OOP_HPP

#include <ctime>
#include <iostream>
#include "mystring.hpp"

using namespace std;

enum NotificationType { TYPE_SYSTEM, TYPE_MESSAGE, TYPE_APP };
enum Severity { NORMAL, URGENT };

class Notification {
protected:
    time_t timestamp;
    NotificationType type;
public:
    Notification(NotificationType t);
    virtual ~Notification() = default;
    virtual void print() const = 0;
    NotificationType getType() const { return type; }
    time_t getTimestamp() const { return timestamp; }
    virtual int getPriorityScore() const;
};

class SystemNotification : public Notification {
private:
    MyString message;
    Severity severity;
public:
    SystemNotification(const char* msg, Severity sev);
    void print() const override;
    int getPriorityScore() const override;
};

class MessageNotification : public Notification {
private:
    MyString contact;
    MyString text;
public:
    MessageNotification(const char* c, const char* t);
    void print() const override;
};

class AppNotification : public Notification {
private:
    MyString appName;
    MyString title;
    MyString text;
public:
    AppNotification(const char* app, const char* ttl, const char* txt);
    void print() const override;
};

int countNotifications(Notification* arr[], size_t size, NotificationType targetType);

#endif