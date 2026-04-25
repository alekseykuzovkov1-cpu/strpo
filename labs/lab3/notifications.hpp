#include <ctime>
#include <cstring>
#include <iostream>

enum NotificationType { TYPE_SYSTEM, TYPE_MESSAGE, TYPE_APP };
enum Severity { NORMAL, URGENT };

struct SystemData {
    char message[128];
    Severity severity;
};

struct MessageData {
    char contact[64];
    char text[128];
};

struct AppData {
    char appName[64];
    char title[64];
    char text[128];
};

struct Notification {
    std::time_t timestamp;
    NotificationType type;
    union {
        SystemData sys;
        MessageData msg;
        AppData app;
    } data;
};
Notification createSystemNotification(const char* msg, Severity sev);
Notification createMessageNotification(const char* contact, const char* text);
Notification createAppNotification(const char* app, const char* title, const char* body);

void printNotification(const Notification& n);
int countNotifications(const Notification* arr, size_t size, NotificationType type);