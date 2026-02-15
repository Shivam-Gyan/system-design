
---

# 🚀 Liskov Substitution Principle (LSP) Guide

> **Core Definition:** Objects of a superclass should be replaceable with objects of its subclasses without affecting the correctness of the program.

---

## 1. The Signature Rules

These rules ensure that the "interface" of the method remains compatible.

### A. Method Signature Rule

The child method must have the same name and parameter types as the parent.

* **Parent:** `void print(string message)`
* **Child:** `void print(string message)` ✅
* **Violation:** Changing parameter types or counts in the child.

### B. Return Type Rule

The child method must return the same type as the parent, or a **subtype** (Covariant Return Types).

* **Parent:** Returns `Animal*`
* **Child:** Returns `Dog*` ✅ (Since `Dog` is an `Animal`)

### C. Exception Rule

A child method should not throw new or broader exceptions than the parent method.

* **Rule:** Subclasses can throw fewer or more specific exceptions, but never broader ones that the client isn't prepared to catch.

---

## 2. The Property Rules (Invariants)

These rules ensure the "internal logic" and "state" of the object remain predictable.

### A. Class Invariant Rule

The child class must respect the constraints set by the parent.

* **Example:** If `Account` requires `balance >= 0`, a `CheatAccount` that allows `balance = -500` violates LSP.
* **Key Takeaway:** If a client assumes an object will always be in State A, the subclass shouldn't allow it to enter State B.

### B. History Constraint Rule

The child class must not modify state that the parent class intended to be immutable or follow a specific progression.

* **Key Takeaway:** If the parent doesn't provide a way to change a variable, the child shouldn't introduce a "backdoor" method to change it.

---

## 3. The Method Rules (Design by Contract)

These define the "contract" between the caller and the method.

### A. Precondition Rule

> *"Require no more, but may require less."*

* **The Rule:** A child class cannot **strengthen** preconditions.
* **Example:** If the Parent accepts any `int`, the Child cannot suddenly require only `positive int`. This would break existing code that sends negative numbers.

### B. Postcondition Rule

> *"Provide no less, but may provide more."*

* **The Rule:** A child class cannot **weaken** postconditions.
* **Example:** If the Parent guarantees that `withdraw()` will update the `balance` immediately, the Child cannot delay that update to a background process, as the client expects an immediate state change.

---

## 💡 Summary Table

| Rule Category | Rule Name | Requirement |
| --- | --- | --- |
| **Contract** | Preconditions | Cannot be strengthened in Child. |
| **Contract** | Postconditions | Cannot be weakened in Child. |
| **Signature** | Return Types | Must be same or subtype (Covariant). |
| **Signature** | Exceptions | No new/broader exceptions. |
| **State** | Invariants | Parent's internal constraints must be preserved. |

---

### 🛠 Code Implementation Tip (C++)

To enforce LSP and prevent accidental errors:

1. Use the `override` keyword to ensure signatures match.
2. Always use **Virtual Destructors** in the base class to ensure proper cleanup when substituting.
3. Avoid `dynamic_cast` to check for specific subtypes; if you have to ask "Are you a Dog?", you are likely violating LSP.

---
