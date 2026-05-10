#include "circle.hpp"
#include <iostream>
using namespace std;

Circle::Circle(double x, double y, double r) : center(x, y), radius(r) {}

Circle::Circle(const Point& p, double r) : center(p), radius(r) {}

void Circle::print() const {
    cout << "Круг [центр: ";
    center.print();
    cout << ", радиус: " << radius << "]";
}

bool Circle::operator==(const Circle& other) const {
    return (radius == other.radius) && (center == other.center);
}

double Circle::getArea() const {
    return 3.14159 * radius * radius;
}

std::ostream& operator<<(std::ostream& os, const Circle& c) {
    os << c.center << " " << c.radius;
    return os;
}

std::istream& operator>>(std::istream& is, Circle& c) {
    is >> c.center >> c.radius;
    return is;
}