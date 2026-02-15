#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Liskov Substitution Principle (LSP) Guidelines


// Signature Rule: method rule - The signature of the method in the child class must be the same as that of the parent class.
// class Parent{
//     public:
//     virtual void print(string message){
//         cout << "Message from Parent: " << message << endl;
//     }
// };

// class Child : public Parent{
//     public:
//         void print(string message) override {
//             cout << "Message from Child: " << message << endl;
//         }
// };

// class Client{
//     private:
//         Parent* parent;

//     public:
//         Client(Parent* parent) : parent(parent) {}

//         void displayMessage(const string& message) {
//             parent->print(message);
//         }
// };

// int main(){
//     Parent* parent = new Parent();
//     Parent* child = new Child(); // LSP: Child can be substituted for Parent
//     child->print("Hello from Child!");

//     parent->print("Hello from Parent!");

//     Client client(child);
//     client.displayMessage("Hello from Client!");

//     delete child;
//     delete parent;
//     return 0;
// }




// Return Type Rule: The return type of the method in the child class must be the same as that of the parent class or a subtype of it.

// class Animal{
//     public:
//     virtual string makeSound(){
//         return "Animal sound";
//     }
//     virtual ~Animal() {} // Virtual destructor to ensure proper cleanup of derived class objects
// };

// class Dog : public Animal{
//     public:
//     string makeSound() override {
//         return "Woof!";
//     }
//     ~Dog() {} // destructor to ensure proper cleanup of derived class objects
// };

// class Parent{
//     public:
//     // if i dont use virtual here then it will not be possible to override the method in the child class and it will violate the LSP
//     // and in Client class when we call getAnimal() method it will always return an Animal* object and not a Dog* object which is a subtype of Animal* and it will violate the LSP
//     virtual Animal* getAnimal(){
//         return new Animal();
//     }
//     virtual ~Parent() {} // Virtual destructor to ensure proper cleanup of derived class objects
// };

// class Child : public Parent{
//     public:
//     Dog* getAnimal() override { // LSP: Return type is a subtype of the parent class's return type
//         return new Dog();
//     }
//     ~Child() {} // destructor to ensure proper cleanup of derived class objects
// };

// class Client{
//     private:
//         Parent* parent; // it can store the reference of both Parent and Child class objects

//     public:
//         Client(Parent* parent) : parent(parent) {} // Constructor to initialize the parent pointer

//         void displayAnimalSound() {
//             Animal* animal = parent->getAnimal(); // LSP: We can call getAnimal() on the parent pointer, and it will return an Animal* (or a subtype, like Dog*)
//             cout << "Animal Sound: " << animal->makeSound() << endl;
//             delete animal; // Clean up memory
//         }
// };

// int main(){

//     Parent* parent = new Parent();
//     Child* child = new Child(); // LSP: Child can be substituted for Parent
//     Client client(parent);
//     client.displayAnimalSound(); // Output: Animal Sound: Animal sound

//     Client childClient(child); // LSP: We can use a Child object where a Parent object is expected
//     childClient.displayAnimalSound(); // Output: Animal Sound: Woof!

//     delete parent;
//     delete child;
//     return 0;
// }


// Exception Rule: The method in the child class must not throw exceptions that are not thrown by the method in the parent class.

 