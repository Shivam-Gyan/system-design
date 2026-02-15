// ISP (Interface Segregation Principle): Clients should not be forced to depend on 
// interfaces they don't use. Create smaller, more specific interfaces.

#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Basic interface for 2D shapes - only requires area calculation
class Shape{
    public:
    virtual void area()=0;
    virtual ~Shape() = default;
};

// Segregated interface for 3D shapes - adds volume capability
// Follows ISP by separating 3D-specific behavior into its own interface
class shape3d : public Shape{
    public:
    virtual void area()=0;
    virtual void volume() = 0;
    virtual ~shape3d() = default;
};

// 2D shape implementation - only implements what it needs (area)
class circle: public Shape{
    public:
    void area() override{
        cout<<"Area of circle is pi*r^2"<<endl;
    }
};

// 3D shape implementation - implements both area and volume
class Sphere: public shape3d{
    public:
    void area() override{
        cout<<"Area of sphere is 4*pi*r^2"<<endl;
    }
    void volume() override{
        cout<<"Volume of sphere is (4/3)*pi*r^3"<<endl;
    }
};

// Client depends only on Shape interface, not on unnecessary methods
class Client{
    private:
    Shape* shape;  

    public:
    Client(Shape* s): shape(s) {}
    void displayArea(){
        shape->area();
    }
};

int main(){
    // Circle uses Shape interface
    Shape* c = new circle();
    Client client(c);
    client.displayArea();

    // Sphere uses shape3d interface which extends Shape
    Shape* s = new Sphere();
    Client client2(s);
    client2.displayArea();

    return 0;
}