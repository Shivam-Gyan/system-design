
---

# 📘 Liskov Substitution Principle (LSP) – Bank Account Example

---

# 🔷 1️⃣ What is LSP?

> **Objects of a derived class must be substitutable for objects of the base class without breaking the correctness of the program.**

In simple words:

If:

```
Derived IS-A Base
```

Then:

```
Derived must behave like Base.
```

---

# 🎯 Why LSP Is Important

Inheritance is not just:

```
extends
```

It is a **behavioral contract**.

If a derived class breaks expectations of the base class:

* Polymorphism breaks
* System becomes unstable
* Open Closed Principle fails

---

# 🏦 2️⃣ Our Banking Example Structure

We designed the system like this:

```
NoWithdrawableAccount  (Base Interface)
        ↑
WithdrawableAccount (Extended Interface)
        ↑
SavingAccount
CurrentAccount

FixedDepositAccount
```

---

# 🔍 3️⃣ Why We Designed It This Way

We separated accounts into:

### 🟢 Accounts that DO NOT support withdrawal

* FixedDepositAccount

### 🔵 Accounts that DO support withdrawal

* SavingAccount
* CurrentAccount

This separation is crucial for LSP.

---

# 🚨 What Would Be LSP Violation?

Imagine we wrote this instead:

```cpp
class Account {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};
```

Then:

```cpp
class FixedDepositAccount : public Account {
public:
    void withdraw(double amount) override {
        throw runtime_error("Withdrawal not allowed!");
    }
};
```

⚠ Problem:

Base class says:

```
All Accounts support withdrawal
```

But FixedDepositAccount says:

```
No, I don’t.
```

This breaks substitutability.

This is classic LSP violation.

---

# 🔥 4️⃣ How Your Design Fixes It

You separated responsibilities:

```cpp
class NoWithdrawableAccount {
    virtual void deposit(double amount) = 0;
    virtual double getBalance() const = 0;
};
```

Then:

```cpp
class WithdrawableAccount : public NoWithdrawableAccount {
    virtual void withdraw(double amount) = 0;
};
```

Now:

* FixedDepositAccount inherits only NoWithdrawableAccount
* SavingAccount & CurrentAccount inherit WithdrawableAccount

So:

* No class is forced to implement unsupported behavior
* Substitutability is preserved

---

# 🧠 5️⃣ LSP Contract in This System

### Base Contract of NoWithdrawableAccount:

1. Can deposit money
2. Can check balance

All derived classes respect this.

---

### Base Contract of WithdrawableAccount:

1. Can deposit
2. Can check balance
3. Can withdraw

All derived classes respect this.

---

# 🔄 6️⃣ Substitutability Check

This must work safely:

```cpp
NoWithdrawableAccount* acc = new FixedDepositAccount(3000);
acc->deposit(500);
```

No crash. No unexpected behavior.

---

This must also work:

```cpp
WithdrawableAccount* acc = new SavingAccount(1000);
acc->withdraw(200);
```

No contract violation.

---

If every derived class works correctly in place of its base:

✅ LSP satisfied.

---

# 🔬 7️⃣ Formal LSP Rules

For derived class:

1️⃣ Preconditions cannot be stronger
2️⃣ Postconditions cannot be weaker
3️⃣ Invariants must remain valid

---

# 📌 Example of Preconditions Violation

If base allows:

```
withdraw(any positive amount)
```

But derived allows only:

```
withdraw(amount > 1000)
```

That strengthens precondition → LSP broken.

---

# 📌 Example of Postcondition Violation

If base guarantees:

```
Balance never negative
```

But derived allows negative balance silently:

LSP broken.

---

# 🧩 8️⃣ Why Client Class Is Clean

Your `Client` class:

```cpp
vector<NoWithdrawableAccount*>
vector<WithdrawableAccount*>
```

It clearly separates usage.

It does NOT try to call withdraw on non-withdrawable accounts.

Thus:

* No unsafe casting
* No runtime errors
* No behavior mismatch

LSP respected.

---

# 🔥 9️⃣ Relationship with Other SOLID Principles

| Principle | Role Here                                      |
| --------- | ---------------------------------------------- |
| SRP       | Separate responsibilities of accounts          |
| OCP       | Add new account types without modifying Client |
| LSP       | Ensure derived accounts behave correctly       |
| ISP       | Segregated interfaces (withdraw separated)     |
| DIP       | Client depends on abstractions                 |

Notice:

Your design also demonstrates ISP naturally.

---

# 🎯 10️⃣ Interview-Level Explanation

If interviewer asks:

> How does your banking example follow LSP?

Answer:

> Instead of forcing all account types to implement withdraw(), I segregated interfaces into withdrawable and non-withdrawable accounts. Each derived class respects the behavioral contract of its base interface. Thus, any derived account can safely replace its base type without breaking program correctness.

---

# 🏗 11️⃣ Visual Understanding

Correct Design:

```
NoWithdrawableAccount
        ↑
WithdrawableAccount
        ↑
SavingAccount
CurrentAccount

FixedDepositAccount
```

Incorrect Design (LSP Violation):

```
Account (deposit + withdraw)
        ↑
SavingAccount
        ↑
FixedDepositAccount  ❌ cannot withdraw
```

---

# 🧠 12️⃣ Core Mental Model

LSP is about:

> Behavior, not just inheritance.

If child cannot behave like parent,
Inheritance is wrong.

---

# 🏆 Final Quick Summary

LSP ensures:

* Safe polymorphism
* Correct inheritance
* Behavioral consistency
* No unexpected runtime errors

In your banking example:

* FixedDepositAccount is NOT forced to implement withdraw()
* WithdrawableAccount extends behavior safely
* Client interacts through correct abstraction
* No contract violation

Thus:

```
LSP is satisfied.
```

---

# 🚀 One-Line Takeaway

> If a child class cannot fully behave like its parent, inheritance is wrong.

---
