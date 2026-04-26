#include<iostream>
#include<cmath>
#include<string>
using namespace std;

const double PI = 3.14159265358979;

class Shape {
protected:
    string color;
    double borderThickness;
    double posX, posY;
public:
    Shape(string col, double border, double x, double y)
        : color(col), borderThickness(border), posX(x), posY(y) {}

    virtual void draw() {
        cout << "Drawing shape at (" << posX << "," << posY << ") Color: " << color << endl;
    }
    virtual double calculateArea() = 0;
    virtual double calculatePerimeter() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
    double radius;
public:
    Circle(string col, double border, double x, double y, double r)
        : Shape(col, border, x, y), radius(r) {}

    void draw() override {
        cout << "Drawing Circle | Center: (" << posX << "," << posY
             << ") | Radius: " << radius << " | Color: " << color << endl;
    }
    double calculateArea() override { return PI * radius * radius; }
    double calculatePerimeter() override { return 2 * PI * radius; }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(string col, double border, double x, double y, double w, double h)
        : Shape(col, border, x, y), width(w), height(h) {}

    void draw() override {
        cout << "Drawing Rectangle | Top-left: (" << posX << "," << posY
             << ") | " << width << "x" << height << " | Color: " << color << endl;
    }
    double calculateArea() override { return width * height; }
    double calculatePerimeter() override { return 2 * (width + height); }
};

class Triangle : public Shape {
    double a, b, c;
public:
    Triangle(string col, double border, double x, double y, double a, double b, double c)
        : Shape(col, border, x, y), a(a), b(b), c(c) {}

    void draw() override {
        cout << "Drawing Triangle | Position: (" << posX << "," << posY
             << ") | Sides: " << a << ", " << b << ", " << c << " | Color: " << color << endl;
    }
    double calculateArea() override {
        double s = (a + b + c) / 2;
        return sqrt(s * (s-a) * (s-b) * (s-c));
    }
    double calculatePerimeter() override { return a + b + c; }
};

class Polygon : public Shape {
    int sides;
    double sideLength;
public:
    Polygon(string col, double border, double x, double y, int n, double len)
        : Shape(col, border, x, y), sides(n), sideLength(len) {}

    void draw() override {
        cout << "Drawing " << sides << "-sided Polygon | Side: " << sideLength
             << " | Color: " << color << endl;
    }
    double calculateArea() override {
        return (sides * sideLength * sideLength) / (4 * tan(PI / sides));
    }
    double calculatePerimeter() override { return sides * sideLength; }
};

int main() {
    Circle c("Red", 1.0, 0, 0, 5);
    c.draw();
    cout << "Area: " << c.calculateArea() << " | Perimeter: " << c.calculatePerimeter() << endl;

    Rectangle r("Blue", 1.5, 2, 3, 10, 4);
    r.draw();
    cout << "Area: " << r.calculateArea() << " | Perimeter: " << r.calculatePerimeter() << endl;

    Triangle t("Green", 1.0, 0, 0, 3, 4, 5);
    t.draw();
    cout << "Area: " << t.calculateArea() << " | Perimeter: " << t.calculatePerimeter() << endl;

    Polygon p("Yellow", 2.0, 1, 1, 6, 4);
    p.draw();
    cout << "Area: " << p.calculateArea() << " | Perimeter: " << p.calculatePerimeter() << endl;

    return 0;
}
