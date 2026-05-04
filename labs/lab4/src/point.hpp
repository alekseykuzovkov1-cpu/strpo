#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>

class Point {
private:
    double x_;
    double y_;

public:

    Point(double x = 0.0, double y = 0.0);

    double getX() const;
    double getY() const;

    void setX(double x);
    void setY(double y);
    void set(double x, double y);

    void print() const;

    bool operator==(const Point& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Point& p);
    friend std::istream& operator>>(std::istream& is, Point& p);
};
#endif