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

// same as return type rule but with exception handling instead of return type


// Property Rule: The properties of the child class must be consistent with those of the parent class. This means that if the parent class has certain properties or invariants, the child class must maintain those properties and not violate them.

// 1. Class invariant rule: The child class must maintain the invariants of the parent class. This means that if the parent class has certain conditions or constraints that must always be true, 
// the child class must ensure that those conditions are also true for its own instances.

//  class Account{
//     protected:
//         double balance;

//     public:
//         Account(double initialBalance) : balance(initialBalance) {
//             if (initialBalance < 0) {
//                 throw invalid_argument("Initial balance cannot be negative.");
//             }
//         }

//         virtual void deposit(double amount) {
//             if (amount <= 0) {
//                 throw invalid_argument("Deposit amount must be positive.");
//             }
//             balance += amount;
//         }

//         virtual void withdraw(double amount) {
//             if (amount <= 0) {
//                 throw invalid_argument("Withdrawal amount must be positive.");
//             }
//             if (amount > balance) {
//                 throw runtime_error("Insufficient funds.");
//             }
//             balance -= amount;
//             cout << "Account: Withdrawn " << amount << ". New balance: " << balance << endl;
//         }

//         virtual ~Account() {} // Virtual destructor to ensure proper cleanup of derived class objects
//  };


//  class CheatAccount: public Account{
    
//     public:
//         CheatAccount(double initialBalance) : Account(initialBalance) {
//             // This constructor does not maintain the invariant of the Account class, as it allows for a negative balance.
//         }

//         // This method violates the invariant of the Account class, as it allows for a negative balance.
//         void withdraw(double amount) override {

//             balance -= amount;
//             cout << "CheatAccount: Withdrawn " << amount << ". New balance: " << balance << endl;

//         }

//         ~CheatAccount() {} // destructor to ensure proper cleanup of derived class objects
//  };

// int main(){
//     try {
//         CheatAccount* cheatAccount = new CheatAccount(100);
//         cheatAccount->withdraw(80); // This violates the invariant of the Account class, as it allows for a negative balance.
//         cheatAccount->withdraw(50); // This violates the invariant of the Account class, as it allows for a negative balance.

//         Account* bankAccount = new Account(100); // LSP: CheatAccount can be substituted for Account
//         bankAccount->withdraw(80); // This is fine, as it maintains the invariant of the Account class.
//         bankAccount->withdraw(50); // This will throw an exception, as it violates the
//         delete cheatAccount;
//         delete bankAccount;
//     } catch (const exception& e) {
//         cerr << "Error: " << e.what() << endl;
//     }

//     return 0;
// }


// 2. History Constraint Rule: The child class must not change the history of the parent class. 
// This means that if the parent class has certain behaviors or states that are expected to be consistent over time, 
// the child class must not alter those behaviors or states in a way that violates the expectations of the parent class.


 


// Method Rule: The method in the child class must not change the behavior of the parent class. 
// This means that if the parent class has certain behaviors or expectations, the child class must not alter those behaviors in a way that violates the expectations of the parent class.

//  1. precondition rule: The child class must not strengthen the preconditions of the parent class. This means that if the parent class has certain conditions that must be met before a method can be called, 
// the child class must not require additional conditions that are not met in the parent class.

// 2. postcondition rule: The child class must not weaken the postconditions of the parent class. 
// This means that if the parent class has certain expected outcomes after a method is called, the child class must not produce weaker outcomes than those expected by the parent class.