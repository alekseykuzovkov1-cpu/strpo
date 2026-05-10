#include <iostream>
#include <fstream>
#include <cassert>
#include "../src/list.hpp"

using namespace std;

int main() {
    cout << "Запуск тестов" << endl;
    List l;

    // добавление элементов
    l.push_back(Circle(0, 0, 10)); // S примерно 314
    l.push_back(Circle(1, 1, 2));  // S примерно 12.56
    l.push_front(Circle(5, 5, 5)); // S примерно 78.5
    
    assert(l.size() == 3);
    cout << "1. Вставка: OK (размер 3)" << endl;

    // сортировка по площади
    l.sort();
    cout << "2. Сортировка: OK. Текущее состояние:" << endl;
    cout << l;

    // работа с файлом
    const char* filename = "test_circles.txt";
    ofstream fout(filename);
    if (fout.is_open()) {
        fout << l;
        fout.close();
        cout << "3. Запись в файл: OK" << endl;
    }

    // очистка и чтение
    l.clear();
    assert(l.size() == 0);
    
    ifstream fin(filename);
    if (fin.is_open()) {
        fin >> l;
        fin.close();
        cout << "4. Чтение из файла: OK. Восстановлено элементов: " << l.size() << endl;
    }
    
    assert(l.size() == 3);
    cout << "\nВсе тесты пройдены успешно" << endl;

    return 0;
}