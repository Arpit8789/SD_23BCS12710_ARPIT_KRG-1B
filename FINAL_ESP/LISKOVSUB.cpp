#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class Rectangle {
protected:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    
    virtual ~Rectangle() {}
    
    virtual double area() const {
        return width * height;
    }
    
    virtual double perimeter() const {
        return 2 * (width + height);
    }
    
    virtual void display() const {
        cout << "Rectangle: width=" << width << ", height=" << height << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {}
    
    void display() const override {
        cout << "Square: side=" << width << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

class Parallelogram : public Rectangle {
private:
    double slantHeight;

public:
    Parallelogram(double w, double h, double slant) 
        : Rectangle(w, h), slantHeight(slant) {}
    
    double area() const override {
        return width * height;
    }
    
    double perimeter() const override {
        return 2 * (width + slantHeight);
    }
    
    void display() const override {
        cout << "Parallelogram: width=" << width << ", height=" << height 
             << ", slant=" << slantHeight << endl;
        cout << "  Area: " << area() << endl;
        cout << "  Perimeter: " << perimeter() << endl;
    }
};

class Bird {
public:
    virtual ~Bird() {}
    
    virtual void fly() {
        cout << "Bird is flying" << endl;
    }
    
    virtual void eat() {
        cout << "Bird is eating" << endl;
    }
};

class Penguin : public Bird {
public:
    void fly() override {
        throw runtime_error("Penguins cannot fly!");
    }
    
    void eat() override {
        cout << "Penguin is eating fish" << endl;
    }
};

class Animal {
public:
    virtual ~Animal() {}
    virtual void eat() = 0;
};

class FlyingBird : public Animal {
public:
    virtual void fly() = 0;
};

class Sparrow : public FlyingBird {
public:
    void eat() override { cout << "Sparrow eating seeds" << endl; }
    void fly() override { cout << "Sparrow flying" << endl; }
};

class PenguinFixed : public Animal {
public:
    void eat() override { cout << "Penguin eating fish" << endl; }
};

void printArea(const Rectangle& r) {
    cout << "Area: " << r.area() << endl;
}

double calculateTotalArea(const vector<Rectangle*>& shapes) {
    double total = 0;
    for (const auto& shape : shapes) {
        total += shape->area();
    }
    return total;
}

int main() {
    cout << "========================================" << endl;
    cout << "Liskov Substitution Principle Demo" << endl;
    cout << "========================================" << endl << endl;

    cout << "--- Example 1: Rectangle Hierarchy ---" << endl;
    
    Rectangle rect(5, 3);
    Square sq(4);
    Parallelogram para(6, 4, 5);
    
    rect.display();
    cout << endl;
    
    sq.display();
    cout << endl;
    
    para.display();
    cout << endl;

    cout << "--- Example 2: Polymorphism with LSP ---" << endl;
    
    Rectangle* shapes[] = {
        new Rectangle(5, 3),
        new Square(4),
        new Parallelogram(6, 4, 5)
    };
    
    for (int i = 0; i < 3; i++) {
        cout << "Shape " << i+1 << ": ";
        shapes[i]->display();
        cout << endl;
    }
    
    double total = 0;
    for (int i = 0; i < 3; i++) {
        total += shapes[i]->area();
    }
    cout << "Total Area: " << total << endl << endl;

    cout << "--- Example 3: Function Parameter Polymorphism ---" << endl;
    
    Rectangle r(10, 5);
    Square s(7);
    
    cout << "Rectangle area: "; printArea(r);
    cout << "Square area: "; printArea(s);
    cout << endl;

    cout << "--- Example 4: LSP Violation (Wrong Design) ---" << endl;
    
    Penguin p;
    try {
        p.fly();
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    cout << "--- Example 5: Correct Design (Fixed) ---" << endl;
    
    Sparrow sparrow;
    PenguinFixed penguin;
    
    sparrow.eat();
    sparrow.fly();
    penguin.eat();
    cout << endl;

    cout << "========================================" << endl;
    cout << "LSP Summary:" << endl;
    cout << "========================================" << endl;
    cout << "1. Subclasses must maintain ALL behavior of base class" << endl;
    cout << "2. Subclasses can extend behavior but NOT restrict it" << endl;
    cout << "3. Objects of subclass should work wherever base class is expected" << endl;
    cout << "4. Preconditions cannot be strengthened in subclass" << endl;
    cout << "5. Postconditions cannot be weakened in subclass" << endl;
    
    return 0;
}
