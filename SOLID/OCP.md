
---

# 📘 Open Closed Principle (OCP) – Explained with Shopping Cart Example

---

# 🔷 1. What is Open Closed Principle?

> **Software entities (classes, modules, functions) should be open for extension, but closed for modification.**

### Meaning:

* ✅ You should be able to **add new behavior**
* ❌ Without modifying existing tested code

---

# 🔥 Why OCP is Important

When a class keeps changing:

* Bugs increase
* Testing effort increases
* Code becomes fragile
* High coupling occurs

OCP prevents:

* Repeated editing of stable code
* Violating production reliability

---

# 🛒 2. Basic Shopping Cart (Before OCP)

Imagine this implementation:

```cpp
class ShoppingCart {
private:
    vector<Product> products;

public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    double calculateTotal() {
        double total = 0;

        for (const auto& product : products) {
            total += product.getPrice();
        }

        // Apply discount logic
        if (total > 1000) {
            total *= 0.9; // 10% discount
        }

        return total;
    }
};
```

---

# ❌ Problem Here

Now business changes:

* Add Festival Discount
* Add Membership Discount
* Add Coupon Discount
* Add Buy-1-Get-1
* Add Student Discount

Every time we must modify:

```cpp
calculateTotal()
```

That violates OCP because:

* Class is NOT closed for modification
* Every new feature forces editing existing code

---

# 🚨 This Causes:

* Risk of breaking old logic
* Hard testing
* Large conditional blocks
* Poor scalability

---

# ✅ Applying OCP Properly

We must separate:

> Discount behavior from ShoppingCart

We achieve this using **Abstraction + Polymorphism**

---

# 🔷 Step 1: Create Discount Strategy Interface

```cpp
class DiscountStrategy {
public:
    virtual double applyDiscount(double total) const = 0;
    virtual ~DiscountStrategy() = default;
};
```

Now we have an abstraction.

---

# 🔷 Step 2: Create Different Discount Types

### 🔹 No Discount

```cpp
class NoDiscount : public DiscountStrategy {
public:
    double applyDiscount(double total) const override {
        return total;
    }
};
```

---

### 🔹 Percentage Discount

```cpp
class PercentageDiscount : public DiscountStrategy {
private:
    double percentage;

public:
    PercentageDiscount(double percentage)
        : percentage(percentage) {}

    double applyDiscount(double total) const override {
        return total * (1 - percentage / 100);
    }
};
```

---

### 🔹 Flat Discount

```cpp
class FlatDiscount : public DiscountStrategy {
private:
    double amount;

public:
    FlatDiscount(double amount)
        : amount(amount) {}

    double applyDiscount(double total) const override {
        return total - amount;
    }
};
```

---

# 🔷 Step 3: Modify ShoppingCart (Only Once)

```cpp
class ShoppingCart {
private:
    vector<Product> products;
    const DiscountStrategy* discountStrategy;

public:
    ShoppingCart(const DiscountStrategy* strategy)
        : discountStrategy(strategy) {}

    void addProduct(const Product& product) {
        products.push_back(product);
    }

    double calculateTotal() const {
        double total = 0;

        for (const auto& product : products) {
            total += product.getPrice();
        }

        return discountStrategy->applyDiscount(total);
    }
};
```

---

# 🔥 What Just Happened?

ShoppingCart now:

* Does NOT know which discount type exists
* Does NOT change when new discount is added
* Only depends on abstraction

---

# 🎯 Now Adding New Discount

Let’s say business wants:

> Festival Discount (20%)

We simply add:

```cpp
class FestivalDiscount : public DiscountStrategy {
public:
    double applyDiscount(double total) const override {
        return total * 0.8;
    }
};
```

That’s it.

No changes to:

* ShoppingCart
* Existing discount classes

---

# 🔒 Why This Follows OCP

| Rule                       | Status |
| -------------------------- | ------ |
| Open for extension         | ✅ Yes  |
| Closed for modification    | ✅ Yes  |
| No editing old stable code | ✅ Yes  |

---

# 🧠 Key Design Concepts Used

* Abstraction
* Polymorphism
* Strategy Pattern
* Dependency Injection

---

# 📌 Before vs After OCP

| Without OCP         | With OCP            |
| ------------------- | ------------------- |
| if-else logic grows | New classes added   |
| Edit existing code  | Extend behavior     |
| High risk of bugs   | Stable architecture |
| Hard to test        | Easy to test        |

---

# 🏗 Real-World Meaning

In production systems:

* Payment methods
* Tax calculation
* Pricing rules
* Notification channels

All should follow OCP.

Because business rules change frequently.

---

# 🧠 Deep Insight

OCP is NOT about:

* Making too many classes
* Overengineering

It is about:

> Designing stable core + flexible extensions

---

# 🎯 Final Mental Model

Think like this:

Instead of:

```
Add new feature → Modify existing class
```

Design like:

```
Add new feature → Create new class
```

---

# 🏆 Interview Explanation (Short Version)

If interviewer asks:

> How did you apply OCP in ShoppingCart?

Answer:

> I extracted discount logic into a strategy interface.
> ShoppingCart depends on abstraction, not concrete implementations.
> New discounts can be added without modifying existing code, satisfying Open Closed Principle.

---

# 🚀 Summary

Open Closed Principle ensures:

* Scalability
* Maintainability
* Extensibility
* Reduced bug risk

Using:

* Strategy Pattern
* Polymorphism
* Dependency Injection

---
