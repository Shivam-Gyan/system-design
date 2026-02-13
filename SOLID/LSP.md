
---

# 📘 Liskov Substitution Principle (LSP) – Explained with Shopping Cart Example

---

# 🔷 1. What is Liskov Substitution Principle?

> **Objects of a derived class must be substitutable for objects of the base class without breaking the correctness of the program.**

Introduced by:
Barbara Liskov (1987)

---

# 🎯 Simple Meaning

If:

```
Derived IS-A Base
```

Then you should be able to replace:

```
Base object → with → Derived object
```

Without breaking behavior.

---

# 🔥 Why LSP Exists

Inheritance is dangerous if misused.

Just because:

```
Dog extends Animal
```

Does NOT mean:

Dog behaves correctly in all contexts where Animal is expected.

LSP ensures:

* Correct inheritance design
* Behavioral consistency
* Safe polymorphism

---

# 🛒 2. Applying LSP to Our Shopping Cart Example

We already defined:

```cpp
class Discount {
public:
    virtual double apply(double total) const = 0;
    virtual ~Discount() = default;
};
```

And derived classes:

* NoDiscount
* PercentageDiscount
* FlatDiscount

ShoppingCart depends on:

```cpp
Discount* discount;
```

---

# 🎯 LSP Rule in This Context

If ShoppingCart expects:

```cpp
Discount* discount
```

Then ANY derived class must:

* Respect expected behavior
* Not break assumptions
* Not change contract

---

# 🔎 What Is the Contract Here?

The implicit contract of `Discount::apply` is:

1. It returns a valid final price.
2. It does not modify cart.
3. It should not return negative total.
4. It should behave logically for any valid input.

All derived classes must follow this.

---

# ✅ Correct LSP-Compliant Discount

Example:

```cpp
class PercentageDiscount : public Discount {
private:
    double percentage;

public:
    PercentageDiscount(double percentage)
        : percentage(percentage) {}

    double apply(double total) const override {
        return total * (1 - percentage / 100);
    }
};
```

This respects contract.

---

# ❌ Example of LSP Violation

Imagine someone writes:

```cpp
class BrokenDiscount : public Discount {
public:
    double apply(double total) const override {
        return -100;  // Always negative
    }
};
```

Now what happens?

ShoppingCart assumes:

```
apply(total) → valid discounted price
```

But this class violates that expectation.

Program logic breaks.

That is LSP violation.

---

# 🔥 Another LSP Violation Example

```cpp
class ExceptionDiscount : public Discount {
public:
    double apply(double total) const override {
        throw runtime_error("Cannot apply discount");
    }
};
```

Now ShoppingCart must suddenly handle exceptions.

Base class never indicated this behavior.

This breaks substitutability.

---

# 🧠 Deep Understanding of LSP

LSP is about:

> Behavioral compatibility

Not just syntax compatibility.

Even if code compiles:

It may still violate LSP.

---

# 📌 Formal LSP Conditions

For Derived class:

1. Preconditions must NOT be stronger than base.
2. Postconditions must NOT be weaker.
3. Invariants must be preserved.

---

# 🛒 Example of Preconditions Violation

Base contract:

```
apply(double total) works for any total ≥ 0
```

Derived class:

```cpp
double apply(double total) const override {
    if (total < 1000)
        throw runtime_error("Minimum 1000 required");
    return total * 0.9;
}
```

Now it requires stronger condition.

This violates LSP.

---

# 🔄 Substitutability Test

If this works:

```cpp
Discount* discount = new PercentageDiscount(10);
ShoppingCart cart(discount);
```

Then this must also work:

```cpp
Discount* discount = new FlatDiscount(200);
ShoppingCart cart(discount);
```

And also:

```cpp
Discount* discount = new NoDiscount();
ShoppingCart cart(discount);
```

Without any modification to ShoppingCart.

That is LSP compliance.

---

# 🏗 Relationship Between OCP and LSP

OCP depends on LSP.

Why?

If derived classes break behavior,
Then extension will break system.

So:

```
OCP requires LSP
```

If LSP fails → OCP collapses.

---

# 🧠 Real-World Meaning

LSP prevents bad inheritance design.

Classic violation example:

```
Rectangle
Square extends Rectangle
```

If Rectangle has:

```
setWidth()
setHeight()
```

Square overriding them breaks expected behavior.

That violates LSP.

---

# 🛒 In Our System

We are safe because:

* All discount types behave consistently.
* They only change how total is computed.
* They don’t introduce unexpected side effects.

Thus:

```
PercentageDiscount IS substitutable for Discount
FlatDiscount IS substitutable for Discount
NoDiscount IS substitutable for Discount
```

LSP satisfied.

---

# 🎯 Interview Explanation (Short Version)

If asked:

> How does your ShoppingCart follow LSP?

Answer:

> All discount types inherit from the Discount interface and respect its behavioral contract. Any derived discount class can replace the base Discount type without breaking ShoppingCart logic, ensuring safe polymorphism.

---

# 🔥 Difference Between OCP and LSP

| OCP                                        | LSP                                    |
| ------------------------------------------ | -------------------------------------- |
| About extension                            | About correctness                      |
| Add new classes without modifying old ones | Ensure derived classes behave properly |
| Structural design principle                | Behavioral design principle            |

---

# 🧠 Final Mental Model

OCP says:

> You can extend system.

LSP says:

> Your extensions must not break system.

Both are required for clean architecture.

---

# 🏆 Final Summary

Liskov Substitution Principle ensures:

* Safe inheritance
* Predictable polymorphism
* Stable system behavior
* Clean architecture

In ShoppingCart:

* Base abstraction: Discount
* Derived classes respect contract
* ShoppingCart remains unchanged
* Behavior remains correct
