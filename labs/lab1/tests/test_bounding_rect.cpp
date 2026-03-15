#include "../src/rect.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>
using namespace std;

// вспомогательная функция для нормализации прямоугольника
Rect normalize_rect(const Rect& r) {
    int left = min(r.get_left(), r.get_right());
    int right = max(r.get_left(), r.get_right());
    int top = min(r.get_top(), r.get_bottom());
    int bottom = max(r.get_top(), r.get_bottom());
    return Rect(left, right, top, bottom);
}

int main() {
    cout << "Запуск тестов bounding_rect..." << endl;
    
    // 1. обычный случай
    {
        Rect r1(0, 10, 0, 10);
        Rect r2(20, 30, 20, 30);
        Rect result = bounding_rect(r1, r2);
        assert(result.get_left() == 0);
        assert(result.get_right() == 30);
        assert(result.get_top() == 0);
        assert(result.get_bottom() == 30);
        cout << "Обычный случай работает исправно" << endl;
    }
    
    // 2. пользователь перепутал left и right
    {
        Rect r1(20, 10, 0, 10);  // left > right
        Rect r2(0, 30, 0, 20);
        Rect result = bounding_rect(r1, r2);
        
        // нормализуем перед проверкой
        assert(result.get_left() == 0);
        assert(result.get_right() == 30);
        assert(result.get_top() == 0);
        assert(result.get_bottom() == 20);
        cout << "Перепутаны left/right работает исправно" << endl;
    }
    
    // 3. пользователь перепутал top и bottom
    {
        Rect r1(0, 10, 20, 10);  // top > bottom
        Rect r2(0, 20, 0, 30);
        Rect result = bounding_rect(r1, r2);
        
        assert(result.get_left() == 0);
        assert(result.get_right() == 20);
        assert(result.get_top() == 0);
        assert(result.get_bottom() == 30);
        cout << "Перепутаны top/bottom работает исправно" << endl;
    }
    
    // 4. пользователь перепутал и left/right, и top/bottom
    {
        Rect r1(30, 10, 40, 20);  // left > right, top > bottom
        Rect r2(0, 20, 0, 30);
        Rect result = bounding_rect(r1, r2);
        
        // нормализуем перед проверкой
        assert(result.get_left() == 0);
        assert(result.get_right() == 30);
        assert(result.get_top() == 0);
        assert(result.get_bottom() == 40);
    }
    
    cout << "Все тесты bounding_rect пройдены" << endl;
    return 0;
}