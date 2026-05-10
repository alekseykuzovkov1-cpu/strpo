#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "point.hpp"

class Circle {
private:
    Point center;
    double radius;

public:
    Circle(double x = 0.0, double y = 0.0, double r = 0.0);
    Circle(const Point& p, double r);

    void print() const;
    
    double getRadius() const;
    const Point& getCenter() const;

    double getArea() const;

    friend std::ostream& operator<<(std::ostream& os, const Circle& c);
    friend std::istream& operator>>(std::istream& is, Circle& c);

    bool operator==(const Circle& other) const;
};

#endif