#include "../src/rect.hpp"
#include <cassert>
#include <iostream>
using namespace std;

int main() {
    cout << "Запуск тестов свойств Rect..." << endl;
    
    // 1. тест get_width и get_height
    {
        Rect r(10, 50, 20, 80);
        assert(r.get_width() == 40);
        assert(r.get_height() == 60);
        cout << "get_width/get_height работает исправно" << endl;
    }
    
    // 2. тест get_square
    {
        Rect r(0, 10, 0, 20);
        assert(r.get_square() == 200);
        cout << "get_square работает исправно" << endl;
    }
    
    // 3. тест set_width
    {
        Rect r;
        r.set_width(30);
        assert(r.get_width() == 30);
        assert(r.get_right() == 30);
        cout << "set_width работает исправно" << endl;
    }
    
    // 4. тест set_height
    {
        Rect r;
        r.set_height(40);
        assert(r.get_height() == 40);
        assert(r.get_bottom() == 40);
        cout << "set_height работает исправно" << endl;
    }
    
    cout << "Все тесты свойств пройдены" << endl;
    return 0;
}