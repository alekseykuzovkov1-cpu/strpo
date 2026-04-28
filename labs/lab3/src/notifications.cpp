/*
#include "notifications.hpp"

Notification createSystemNotification(const char* msg, Severity sev) {
    Notification n;
    n.timestamp = time(nullptr);
    n.type = TYPE_SYSTEM;
    strncpy(n.data.sys.message, msg, 127);
    n.data.sys.severity = sev;
    return n;
}


Notification createMessageNotification(const char* contact, const char* text) {
    Notification n;
    n.timestamp = time(nullptr);
    n.type = TYPE_MESSAGE;
    strncpy(n.data.msg.contact, contact, 63);
    strncpy(n.data.msg.text, text, 127);
    return n;
}


Notification createAppNotification(const char* app, const char* title, const char* body) {
    Notification n;
    n.timestamp = time(nullptr);
    n.type = TYPE_APP;
    strncpy(n.data.app.appName, app, 63);
    strncpy(n.data.app.title, title, 63);
    strncpy(n.data.app.text, body, 127);
    return n;
}

void printNotification(const Notification& n) {
    cout << "[" << n.timestamp << "] ";
    switch (n.type) {
        case TYPE_SYSTEM:
            cout << "Системное " << (n.data.sys.severity == URGENT ? "!!! " : "") 
                      << n.data.sys.message << "\n";
            break;
        case TYPE_MESSAGE:
            cout << "Мгновенное от: " << n.data.msg.contact 
                      << " | сообщение: " << n.data.msg.text << "\n";
            break;
        case TYPE_APP:
            cout << "Приложение " << n.data.app.appName << ": " 
                      << n.data.app.title << " - " << n.data.app.text << "\n";
            break;
    }
}


int countNotifications(const Notification* arr, size_t size, NotificationType type) {
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i].type == type) {
            count++;
        }
    }
    return count;
}
*/