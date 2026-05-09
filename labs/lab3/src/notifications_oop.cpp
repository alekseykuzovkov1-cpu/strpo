
#include "notifications_oop.hpp"

Notification::Notification(NotificationType t) : timestamp(time(nullptr)), type(t) {}

int Notification::getPriorityScore() const {
    if (type == TYPE_MESSAGE) return 10;
    if (type == TYPE_SYSTEM) return 20;
    return 30;
}

SystemNotification::SystemNotification(const char* msg, Severity sev) 
    : Notification(TYPE_SYSTEM), message(msg), severity(sev) {}

void SystemNotification::print() const {
    cout << "Системное" << (severity == URGENT ? "!!!: " : ": ") 
         << message << endl;
}

int SystemNotification::getPriorityScore() const {
    if (severity == URGENT) return 0;
    return 20;
}

MessageNotification::MessageNotification(const char* c, const char* t) 
    : Notification(TYPE_MESSAGE), contact(c), text(t) {}

void MessageNotification::print() const {
    cout << "Мгновенное от: " << contact << " | сообщение: " << text << endl;
}

AppNotification::AppNotification(const char* app, const char* ttl, const char* txt) 
    : Notification(TYPE_APP), appName(app), title(ttl), text(txt) {}

void AppNotification::print() const {
    cout << "Приложение " << appName << " | " << title << ": " << text << endl;
}

int countNotifications(Notification* arr[], size_t size, NotificationType targetType) {
    int count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (arr[i]->getType() == targetType) {
            count++;
        }
    }
    return count;
}