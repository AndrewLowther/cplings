#include <iostream>
#include <string>
#include <vector>

// classes4.cpp
// Make me compile! Go to the folder hint if you want a hint :)

// We sometimes encourage you to keep trying things on shape given exercise,
// even after you already figured it out. 

// Step 1: Make me compile!
// Write the Circle constructor

struct Point {
    static const double epsilon;
    double x;
    double y;
    // When two points are close to each other we assume that they are equal
    bool operator==(const Point& p) const{
        return (std::abs(x - p.x) < epsilon) &&
               (std::abs(y - p.y) < epsilon);
    }
};
const double Point::epsilon = 1e-6;

// Display value for a point
std::ostream& operator<< (std::ostream& out, const Point & p) {
    return out << "{" << p.x << ", " << p.y << "}";
}

constexpr Point point_zero = { 0.0, 0.0 };

class Shape {
public:
    Point center_;
    Shape(const Point & centre = point_zero) : center_(centre) { }

    virtual Point center() const  {
        return point_zero;
    }
};

class Circle : public Shape {
public:
    Circle(const Point& centre = point_zero) : Shape(centre) { } 

    virtual Point center() const {
        return Circle::center_;
    }
};

std::vector<Point> test_center() {
    const Shape shape;
    const Point point_in{ 1.0, 1.0 };
    const Circle circle(point_in);
    std::vector<Shape*> shape_collection;
    // TODO: Figure out what this is doing, presumably it's casting?
    // Seemingly so: https://cplusplus.com/articles/iG3hAqkS/
    // It seems happy enough casting to a pointer here
    shape_collection.push_back((Shape*) &shape);
    shape_collection.push_back((Shape*) &circle);  // Fix: Virtual calls work with references and addresses

    // TODO: Why does wrapping this in brackets work? 
    // Element must have a class but it has type.
    // it seems like this is an ambiguity case: https://cplusplus.com/forum/beginner/138279/
    // wrapping in brackets removes the ambiguity
    std::vector<Point> center_collection{ (*shape_collection[0]).center(), // Fix: Virtual calls work with references and addresses
                                                (*shape_collection[1]).center() };
    std::cout << "Value :" << center_collection[0] << "\n";
    std::cout << "Value :" << center_collection[1] << "\n";
    return center_collection;
}


#include <catch2/catch.hpp>

TEST_CASE("test_vtable") {
    const Point point_in{ 1.0, 1.0 };
    auto center_collection = test_center();

    REQUIRE(center_collection[0] == point_zero);
    REQUIRE(center_collection[1] == point_in);
}
