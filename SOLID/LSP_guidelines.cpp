#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Liskov Substitution Principle (LSP) Guidelines


// Signature Rule: method rule - The signature of the method in the child class must be the same as that of the parent class.
class Parent{
    virtual void print(string message) = 0;
};

class Child : public Parent{
    public:
        void print(string message) override {
            cout << "Message from Child: " << message << endl;
        }
};

int main(){
    Child child;
    child.print("Hello from Child!");
    return 0;
}