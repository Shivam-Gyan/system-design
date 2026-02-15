#include<iostream>
#include<bits/stdc++.h>
using namespace std;



// abstract class / interface for persistence 
class Persistence{

    public:
        virtual void save() = 0;
        virtual ~Persistence() = default;
};


// Concrete implementations of Persistence interface for different storage types
class MySQl: public Persistence{

    public:
        void save() override{
            cout<<"Saving to MySQL database"<<endl;
        }
};


// Another implementation of Persistence interface for MongoDB
class MongoDB : public Persistence{

    public:
        void save() override{
            cout<<"Saving to MongoDB database"<<endl;
        }
};


class Application{
    private:
        Persistence& persistence;

    public:
        Application(Persistence& p): persistence(p) {}

        void saveData(){
            persistence.save();
        }
};


int main(){

    // creating a MySQL persistence and using it in the application
    MySQl mysql; // using parent interface type for flexibility
    Application app1(mysql); // injecting MySQL persistence into the application
    app1.saveData(); // client code only depends on Persistence interface, not on MySQL-specific details

    MongoDB mongo; // using parent interface type for flexibility
    Application app2(mongo); // injecting MongoDB persistence into the application
    app2.saveData(); // client code only depends on Persistence interface, not on MongoDB-specific details

    return 0;
}