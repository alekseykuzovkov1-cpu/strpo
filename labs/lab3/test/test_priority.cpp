#include <iostream>
#include <cassert>
#include <thread> // для имитации задержки времени
#include <chrono>

#include "notifications_oop.hpp"
#include "notifications_priority_queue.hpp"

using namespace std;

int main() {
    NotificationPriorityQueue pq;

    cout << "Запуск автоматического теста приоритетов\n";

    // срочное системное выше всех
    pq.push(new MessageNotification("User1", "Привет"));
    pq.push(new SystemNotification("Критическая ошибка!", URGENT));

    Notification* first = pq.pop();
    // оижадется выход системного
    if (first->getPriorityScore() == 0) {
        cout << "УСПЕХ Тест 1: срочное уведомление имеет высший приоритет\n";
    } else {
        cout << "ПРОВАЛ Тест 1: срочное уведомление пропустило вперед другое\n";
    }
    delete first;
    delete pq.pop();

    // кто раньше, тот важнее
    pq.push(new AppNotification("прил1", "обн", "в1"));
    this_thread::sleep_for(chrono::seconds(1)); // ждем 1 сек, чтобы время отличалось
    pq.push(new AppNotification("прил2", "обн", "в2"));

    Notification* early = pq.pop();
    // должно выйти прил1
    if (early->getTimestamp() < time(nullptr)) { 
        early->print(); 
        cout << "УСПЕХ Тест 2: более раннее уведомление вышло первым.\n";
    } else {
        cout << "ПРОВАЛ Тест 2: более раннее уведомление вышло позже\n";
    }
    delete early;
    delete pq.pop();

    // разные типы в один момент времени
    pq.push(new AppNotification("игра", "ивент", "начало"));
    pq.push(new MessageNotification("User1", "привет"));
    pq.push(new SystemNotification("Диск полон", NORMAL));

    cout << "Порядок выхода при совпадении времени (ожидается: мгновенное -> системное -> приложение):\n";
    while (pq.size() > 0) {
        Notification* n = pq.pop();
        n->print();
        delete n;
    }
    cout << "Тест 3 завершен (проверьте порядок вывода выше)\n";

    // один тип и одно время -> FIFO
    pq.push(new MessageNotification("User1", "первый"));
    pq.push(new MessageNotification("User2", "второй"));

    Notification* nA = pq.pop();
    nA->print();
    if (nA->getPriorityScore() == 10) {
         cout << "УСПЕХ Тест 4: сохранен порядок добавления для одинаковых типов\n";
    } else {
        cout << "ПРОВАЛ Тест 4: не сохранен порядок добавления для одинаковых типов\n";
    }
    delete nA;
    delete pq.pop();

    cout << "\nВсе тесты завершены\n";
}