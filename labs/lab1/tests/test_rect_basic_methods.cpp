#include "../src/rect.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cout << "Запуск тестов Rect..." << endl;
    // 1. конструктор по умолчанию
    Rect r1;
    assert(r1.get_left() == 0);
    assert(r1.get_right() == 0);
    assert(r1.get_top() == 0);
    assert(r1.get_bottom() == 0);
    cout << "Конструктор по умолчанию работает исправно" << endl;
        
    // 2. параметризованный конструктор
    Rect r2(10, 20, 30, 40);
    assert(r2.get_left() == 10);
    assert(r2.get_right() == 20);
    assert(r2.get_top() == 30);
    assert(r2.get_bottom() == 40);
    cout << "Параметризованный конструктор работает исправно" << endl;
        
    // 3. конструктор копирования
    Rect r3(r2);
    assert(r3.get_left() == 10);
    assert(r3.get_right() == 20);
    assert(r3.get_top() == 30);
    assert(r3.get_bottom() == 40);
    cout << "Конструктор копирования работает исправно" << endl;
        
    // 4. set_all
    Rect r4;
    r4.set_all(5, 15, 25, 35);
    assert(r4.get_left() == 5);
    assert(r4.get_right() == 15);
    assert(r4.get_top() == 25);
    assert(r4.get_bottom() == 35);
    cout << "set_all() работает исправно" << endl;
        
    cout << "Все тесты пройдены" << endl;
    return 0;    
}