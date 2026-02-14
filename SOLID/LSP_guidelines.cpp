#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Liskov Substitution Principle (LSP) Guidelines


// Signature Rule: method rule - The signature of the method in the child class must be the same as that of the parent class.
class Parent{
    public:
    virtual void print(string message){
        cout << "Message from Parent: " << message << endl;
    }
};

class Child : public Parent{
    public:
        void print(string message) override {
            cout << "Message from Child: " << message << endl;
        }
};

class Client{
    private:
        Parent* parent;

    public:
        Client(Parent* parent) : parent(parent) {}

        void displayMessage(const string& message) {
            parent->print(message);
        }
};

int main(){
    Child child;
    Parent* parentPtr = new Parent(); // LSP: Child can be substituted for Parent
    child.print("Hello from Child!");
    parentPtr->print("Hello from Parent!");
    Client client(parentPtr);
    
    client.displayMessage("Hello from Client!");

    delete parentPtr;
    return 0;
}