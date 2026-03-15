#include "../src/rect.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cout << "Запуск тестов операций Rect..." << endl;
    
    // 1. тест move
    {
        Rect r(10, 20, 30, 40);
        r.move(5, 5);
        assert(r.get_left() == 15);
        assert(r.get_right() == 25);
        assert(r.get_top() == 35);
        assert(r.get_bottom() == 45);
        cout << "move работает исправно" << endl;
    }
    
    // 2. тест inflate (один параметр)
    {
        Rect r(10, 20, 30, 40);
        r.inflate(2);
        assert(r.get_left() == 8);
        assert(r.get_right() == 22);
        assert(r.get_top() == 28);
        assert(r.get_bottom() == 42);
        cout << "inflate (один параметр) работает исправно" << endl;
    }
    
    // 3. тест inflate (два параметра)
    {
        Rect r(10, 20, 30, 40);
        r.inflate(3, 4);
        assert(r.get_left() == 7);
        assert(r.get_right() == 23);
        assert(r.get_top() == 26);
        assert(r.get_bottom() == 44);
        cout << "inflate (два параметра) работает исправно" << endl;
    }
    
    // 4. тест inflate (четыре параметра)
    {
        Rect r(10, 20, 30, 40);
        r.inflate(1, 2, 3, 4);
        assert(r.get_left() == 9);
        assert(r.get_right() == 22);
        assert(r.get_top() == 27);
        assert(r.get_bottom() == 44);
        cout << "inflate (четыре параметра) работает исправно" << endl;
    }
    
    cout << "Все тесты операций пройдены" << endl;
    return 0;
}