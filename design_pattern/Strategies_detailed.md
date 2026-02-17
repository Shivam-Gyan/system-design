## Strategy Design Pattern

The **Strategy Pattern** is a behavioral design pattern that allows you to define a family of algorithms, encapsulate each one, and make them interchangeable. It enables selecting an algorithm's behavior at runtime without changing the classes that use it.

---

### Core Concept: "Composition Over Inheritance"

The Strategy Pattern is the primary solution to **"Inheritance Hell"**. Instead of creating a massive tree of subclasses for every possible combination of behaviors (which leads to a combinatorial explosion of classes), you view an object as a **collection of swappable behaviors**.

* **Relationship:** It shifts from an **"Is-A"** relationship (Inheritance) to a **"Has-A"** relationship (Composition).
* **Flexibility:** Behaviors are encapsulated in separate classes and can be swapped at runtime.

---

### Key Components

1. **Strategy Interface:** An abstract class or interface common to all supported algorithms.
2. **Concrete Strategies:** Classes that implement the specific algorithms using the Strategy interface.
3. **Context:** The class that maintains a reference to a Strategy object and delegates the work to it.

---

### Example: Robot Behaviors

In this example, a `Robot` can have different ways of speaking or moving. Instead of hard-coding these into the Robot, we "plug" them in.

```cpp
#include <iostream>
#include <string>

// 1. Strategy Interface
class Talkable {
public:
    virtual void talk() = 0;
    virtual ~Talkable() = default;
};

// 2. Concrete Strategies
class EnglishTalkable : public Talkable {
public:
    void talk() override {
        std::cout << "Hello, I am a robot." << std::endl;
    }
};

class HindiTalkable : public Talkable {
public:
    void talk() override {
        std::cout << "नमस्ते, मैं एक रोबोट हूँ।" << std::endl;
    }
};

// 3. Context
class Robot {
private:
    Talkable* talkStrategy; // Aggregation: Robot HAS-A Talkable strategy

public:
    Robot(Talkable* strategy) : talkStrategy(strategy) {}

    // Allows changing strategy at runtime
    void setTalkStrategy(Talkable* newStrategy) {
        talkStrategy = newStrategy;
    }

    void performTalk() {
        talkStrategy->talk();
    }
};

int main() {
    EnglishTalkable english;
    HindiTalkable hindi;

    // Initialize with English
    Robot myRobot(&english);
    myRobot.performTalk();

    // Swap to Hindi at runtime
    myRobot.setTalkStrategy(&hindi);
    myRobot.performTalk();

    return 0;
}

```

---

### Benefits

* **Open/Closed Principle:** You can introduce new strategies without changing the Context.
* **Isolation:** You can isolate the implementation details of an algorithm from the code that uses it.
* **Runtime Switching:** Objects can change their behavior dynamically while the program is running.