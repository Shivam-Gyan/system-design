#include<iostream>
#include<bits/stdc++.h>
using namespace std;


// Strategy Pattern is a behavioral design pattern that enables selecting an algorithm's behavior at runtime.

//  abstarct class 
class Talkable{
    public:
        virtual void talk()= 0;
        virtual ~Talkable() = default;
};

// implementation of the Talkable interface
class EnglishTalkable: public Talkable{
    public:
        void talk() override{
            cout<<"Hello, I am a robot that can talk in English."<<endl;
        }
};

class HindiTalkable: public Talkable{
    public:
        void talk() override{
            cout<<"Me Hindi Support karta hu !"<<endl;
        }
};

// abstract class
class Walkable{
    public:
        virtual void walk()= 0;
        virtual ~Walkable() = default;
};

// implementation of the Walkable interface
class FastWalkable: public Walkable{
    public:
        void walk() override{
            cout<<"I am a robot that can walk fast."<<endl;
        }
};

class SlowWalkable: public Walkable{
    public:
        void walk() override{
            cout<<"I am a robot that can walk slow."<<endl;
        }
};

// abstract class
class Flyable{
    public:
        virtual void fly()= 0;
        virtual ~Flyable() = default;
};

// implementation of the Flyable interface
class CanFlyable: public Flyable{
    public:
        void fly() override{
            cout<<"I am a robot that can fly."<<endl;
        }
};

class CannotFlyable: public Flyable{
    public:
        void fly() override{
            cout<<"I am a robot that cannot fly."<<endl;
        }
};

//  Robot class that has a relationship with the above abstract classes

class Robot{

    private:
        Talkable* talkable;
        Walkable* walkable;
        Flyable* flyable;

    public:
        Robot(Talkable* talkable, Walkable* walkable, Flyable* flyable): talkable(talkable), walkable(walkable), flyable(flyable){}

        void talk(){
            talkable->talk();
        }

        void walk(){
            walkable->walk();
        }

        void fly(){
            flyable->fly();
        }

        virtual void projetion()= 0;
        virtual ~Robot() = default;
};

class HumanoidRobot: public Robot{
    public:
        HumanoidRobot(Talkable* talkable, Walkable* walkable, Flyable* flyable): Robot(talkable, walkable, flyable){}

        void projetion(){
            cout<<"I am a humanoid robot."<<endl;
        }
};


int main(){

    HindiTalkable hindiSpeech;
    FastWalkable fastWalkable;
    CanFlyable canFlyable;

    HumanoidRobot robot(&hindiSpeech, &fastWalkable, &canFlyable);

    robot.talk();
    robot.walk();
    robot.fly();
    robot.projetion();

    return 0;
}