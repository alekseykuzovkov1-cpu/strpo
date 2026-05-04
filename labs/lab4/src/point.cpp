#include "point.hpp"
#include <iostream>

using namespace std;

Point::Point(double x, double y) : x_(x), y_(y) {}

double Point::getX() const { return x_; }
double Point::getY() const { return y_; }

void Point::setX(double x) { x_ = x; }
void Point::setY(double y) { y_ = y; }

void Point::set(double x, double y) {
    x_ = x;
    y_ = y;
}

void Point::print() const {
    cout << "(" << x_ << ", " << y_ << ")";
}

bool Point::operator==(const Point& other) const {
    return (x_ == other.x_) && (y_ == other.y_);
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << p.x_ << " " << p.y_;
    return os;
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p.x_ >> p.y_;
    return is;
}