#include "rect.hpp"
#include <iostream>
using namespace std;

/*
Rect::Rect() 
    : left(0), right(0), top(0), bottom(0)
{
    cout << "Конструктор по умолчанию для " << this << endl;
}

Rect::Rect(int l, int r, int t, int b) 
    : left(l), right(r), top(t), bottom(b)
{
    cout << "Параметризованный конструктор для " << this << " с параметрами: " << l << "," << r << "," << t << "," << b << endl;
}

Rect::Rect(const Rect& other)
    : left(other.left), right(other.right), top(other.top), bottom(other.bottom) 
{
    cout << "Конструктор копирования для " << this << " из " << &other << endl;
}

Rect::~Rect() {
    cout << "Деструктор для " << this << " с полями: " << left << "," << right << "," << top << "," << bottom << endl;
}

void Rect::set_all(int l, int r, int t, int b) {
    left = l;
    right = r;
    top = t;
    bottom = b;
    cout << "set_all вызван для " << this << " с параметрами: " << l << "," << r << "," << t << "," << b << endl;
}

void Rect::inflate(int amount) {
    left -= amount;
    right += amount;
    top -= amount;
    bottom += amount;
}

void Rect::inflate(int dw, int dh) {
    left -= dw;
    right += dw;
    top -= dh;
    bottom += dh;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    left -= d_left;
    right += d_right;
    top -= d_top;
    bottom += d_bottom;
}

void Rect::move(int dx, int dy) {
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
}
*/

Rect bounding_rect(Rect r1, Rect r2) {
    int r1_left = min(r1.get_left(), r1.get_right());
    int r1_right = max(r1.get_left(), r1.get_right());
    int r1_top = min(r1.get_top(), r1.get_bottom());
    int r1_bottom = max(r1.get_top(), r1.get_bottom());
    
    int r2_left = min(r2.get_left(), r2.get_right());
    int r2_right = max(r2.get_left(), r2.get_right());
    int r2_top = min(r2.get_top(), r2.get_bottom());
    int r2_bottom = max(r2.get_top(), r2.get_bottom());
    
    int min_left = min(r1_left, r2_left);
    int max_right = max(r1_right, r2_right);
    int min_top = min(r1_top, r2_top);
    int max_bottom = max(r1_bottom, r2_bottom);
    
    Rect result(min_left, max_right, min_top, max_bottom);
    
    return result;
}

void print_rect(const Rect& r) {
    cout << "Прямоугольник: ";
    cout << "left=" << r.get_left() << ", right=" << r.get_right();
    cout << ", top=" << r.get_top() << ", bottom=" << r.get_bottom();
    cout << endl;
}

/*
void Rect::set_width(int new_width) {
    if (new_width < 0) {
        cout << "Ошибка: ширина не может быть отрицательной" << endl;
        return;
    }
    right = left + new_width;
}

void Rect::set_height(int new_height) {
    if (new_height < 0) {
        cout << "Ошибка: высота не может быть отрицательной" << endl;
        return;
    }
    bottom = top + new_height;
}
*/
Rect::Rect() 
    : x(0), y(0), w(0), h(0)
{
    cout << "Конструктор по умолчанию для " << this << endl;
}

Rect::Rect(int l, int r, int t, int b) 
    : x(l),
      y(t),
      w(r - l),
      h(b - t)
{
    //гарантируем положительные размеры
    if (w < 0) {
        w = -w;
        x = r;
    }
    if (h < 0) {
        h = -h;
        y = b;  // если bottom < top, меняем
    }
    
    cout << "Параметризованный конструктор для " << this 
              << " с параметрами: " << l << "," << r << "," << t << "," << b 
              << " - храним: x=" << x << ", y=" << y << ", w=" << w << ", h=" << h 
              << endl;
}

Rect::Rect(const Rect& other)
    : x(other.x), y(other.y), w(other.w), h(other.h)
{
    cout << "Конструктор копирования для " << this << " из " << &other << endl;
}

Rect::~Rect() {
    cout << "Деструктор для " << this 
              << " с полями: left=" << get_left() 
              << ", right=" << get_right()
              << ", top=" << get_top() 
              << ", bottom=" << get_bottom()
              << endl;
}

void Rect::set_all(int l, int r, int t, int b) {
    x = l;
    y = b;
    w = r - l;
    h = t - b;
    
    // Гарантируем положительные размеры
    if (w < 0) {
        w = -w;
        x = r;
    }
    if (h < 0) {
        h = -h;
        y = t;
    }
    
    cout << "set_all вызван для " << this 
              << " с параметрами: " << l << "," << r << "," << t << "," << b 
              << endl;
}

void Rect::move(int dx, int dy) {
    x += dx;
    y += dy;
}

void Rect::inflate(int amount) {
    x -= amount;
    w += 2 * amount;
    y -= amount;
    h += 2 * amount;
}

void Rect::inflate(int dw, int dh) {
    x -= dw;
    w += 2 * dw;
    y -= dh;
    h += 2 * dh;
}

void Rect::inflate(int d_left, int d_right, int d_top, int d_bottom) {
    x -= d_left;
    w += d_left + d_right;
    y -= d_top;
    h += d_top + d_bottom;
}

void Rect::set_width(int new_width) {
    if (new_width < 0) {
        cout << "Ошибка: ширина не может быть отрицательной" << endl;
        return;
    }
    w = new_width;
}

void Rect::set_height(int new_height) {
    if (new_height < 0) {
        cout << "Ошибка: высота не может быть отрицательной" << endl;
        return;
    }
    h = new_height;
}
