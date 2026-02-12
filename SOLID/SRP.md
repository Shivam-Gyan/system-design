
# Applying Single Responsibility Principle (SRP) in Shopping Cart Design

## 1. Introduction

In Low-Level Design (LLD), it is important to properly separate responsibilities and choose the correct relationships between classes.

This document explains:

* What SRP (Single Responsibility Principle) means
* Why the initial ShoppingCart design violates SRP
* How to refactor it properly
* Why Composition is NOT suitable in this case
* What would happen if Composition was used incorrectly
* Correct UML arrow directions



# 2. Understanding SRP (Single Responsibility Principle)

## Definition

> A class should have only one reason to change.

This means:

* A class should handle only one responsibility.
* It should not mix business logic, persistence, formatting, etc.

---

# 3. Initial (Incorrect) Design

```java
class ShoppingCart {
    List<Product> products;

    double total() { }
    void invoice() { }
    void saveToDB() { }
}
```

## Why This Violates SRP

ShoppingCart is handling:

| Method     | Responsibility       |
| ---------- | -------------------- |
| total()    | Business logic       |
| invoice()  | Invoice generation   |
| saveToDB() | Database persistence |

This means ShoppingCart has **multiple reasons to change**:

* Pricing rules change
* Invoice format changes
* Database changes

That violates SRP.

---

# 4. Refactored Design (SRP-Compliant)

We split responsibilities into separate classes.

## 4.1 ShoppingCart (Only Product Management)

```java
class ShoppingCart {
    private List<Product> products;

    public List<Product> getProducts() {
        return products;
    }
}
```

Responsibility:

* Only manage products.

---

## 4.2 CartCalculator

```java
class CartCalculator {
    double calculateTotal(ShoppingCart cart) {
        // business logic
    }
}
```

Responsibility:

* Only pricing logic.

---

## 4.3 InvoiceService

```java
class InvoiceService {
    void generateInvoice(ShoppingCart cart) {
        // invoice formatting
    }
}
```

Responsibility:

* Only invoice generation.

---

## 4.4 CartRepository

```java
class CartRepository {
    void save(ShoppingCart cart) {
        // persistence logic
    }
}
```

Responsibility:

* Only database operations.

---

# 5. Relationship Type Between Classes

Now let's analyze the relationships.

---

## 5.1 ShoppingCart → Product

```
ShoppingCart --------> Product
```

Why?

* ShoppingCart holds a list of Product references.
* Product does not depend on ShoppingCart.

This is a **simple association**.

---

## 5.2 Services → ShoppingCart

```
CartCalculator --------> ShoppingCart
InvoiceService --------> ShoppingCart
CartRepository --------> ShoppingCart
```

Why?

* These classes use ShoppingCart.
* They do not own it.
* They do not control its lifecycle.

This is also **simple association (or dependency)**.

---

# 6. Why Composition Is NOT Used Here

## What is Composition?

Composition means:

* Strong ownership
* Lifecycle dependency
* Child cannot exist without parent
* Represented by black diamond (◆)

Example:

```
Car ◆--------> Engine
```

If Car is destroyed → Engine is destroyed.

---

## Does That Apply Here?

Ask:

* If ShoppingCart is deleted, should CartCalculator be destroyed permanently?
* If one cart is removed, should InvoiceService disappear from system?
* Is CartRepository created and destroyed only with a specific cart?

Answer: No.

These classes are independent services.

Therefore:

❌ No lifecycle dependency
❌ No strong ownership
❌ No composition

---

# 7. What If We Use Composition Incorrectly?

Suppose we design:

```
ShoppingCart ◆--------> CartCalculator
```

This would mean:

* Calculator belongs exclusively to that cart
* It cannot exist independently
* It must be created and destroyed with that cart

That creates problems:

1. Tight coupling
2. Harder testing
3. Reduced reusability
4. Violates separation of concerns

You would be mixing service logic into domain logic again.

---

# 8. Key Concept: SRP vs Composition

Very important distinction:

| Concept     | Purpose                        |
| ----------- | ------------------------------ |
| SRP         | Controls responsibility        |
| Composition | Controls ownership & lifecycle |

They are independent.

You can:

* Follow SRP and still use composition (if lifecycle requires it).
* Follow SRP and use only association (if services are independent).

SRP does NOT forbid composition.

Composition is used only when lifecycle dependency exists.

---

# 9. Final UML Summary

```
ShoppingCart --------> Product

CartCalculator --------> ShoppingCart
InvoiceService --------> ShoppingCart
CartRepository --------> ShoppingCart
```

No diamonds.

Only simple associations.

---

# 10. Final Interview-Level Answer

If asked:

> Why didn’t you use composition?

You answer:

Because CartCalculator, InvoiceService, and CartRepository are independent services. They are not lifecycle-bound parts of ShoppingCart. Composition implies strong ownership and lifecycle dependency, which does not exist here.

---

# 11. Final Takeaways

* SRP = One reason to change
* Composition = Strong ownership + lifecycle dependency
* Arrow = Reference direction
* Diamond = Ownership
* Services typically use simple association, not composition

---