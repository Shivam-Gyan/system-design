#include<iostream>
#include<bits/stdc++.h>
using namespace std;

// Abstract/ interface class for accounts that do not support withdrawal
class NoWithdrawableAccount{
    public:
        virtual void deposit(double amount) = 0;
        virtual double getBalance() const = 0;
};

// Abstract/ interface class for accounts that support withdrawal and inherits from NoWithdrawableAccount
class WithdrawableAccount : public NoWithdrawableAccount{
    public:
        virtual void withdraw(double amount) = 0;
};

// Concrete class for saving account that supports withdrawal
class SavingAccount: public WithdrawableAccount{
    private:
        double balance;
    public:
        SavingAccount(double initialBalance) : balance(initialBalance) {}

        void deposit(double amount) override {
            balance += amount;
        }

        double getBalance() const override {
            return balance;
        }

        void withdraw(double amount) override {
            if (amount <= balance) {
                balance -= amount;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        }
};

// Concrete class for current account that supports withdrawal
class CurrentAccount: public WithdrawableAccount{
    private:
        double balance;
    public:
        CurrentAccount(double initialBalance) : balance(initialBalance) {}

        void deposit(double amount) override {
            balance += amount;
        }

        double getBalance() const override {
            return balance;
        }

        void withdraw(double amount) override {
            if (amount <= balance) {
                balance -= amount;
            } else {
                cout << "Insufficient funds!" << endl;
            }
        }
};

// Concrete class for fixed deposit account that does not support withdrawal
class FixedDepositAccount: public NoWithdrawableAccount{
    private:
        double balance;
    public:
        FixedDepositAccount(double initialBalance) : balance(initialBalance) {}

        void deposit(double amount) override {
            balance += amount;
        }

        double getBalance() const override {
            return balance;
        }
};

// Bank client class that uses both types of accounts
class Client{
    private:
        vector<NoWithdrawableAccount*> noWithdrawableAccount;  //like fixed deposit account
        vector<WithdrawableAccount*> withdrawableAccounts; //like saving account and current account
    public:
        Client(const vector<NoWithdrawableAccount*>& noWithdrawableAccount,const vector<WithdrawableAccount*>& withdrawableAccounts) : noWithdrawableAccount(noWithdrawableAccount), withdrawableAccounts(withdrawableAccounts) {}

        // Method to display balances of all accounts without violating LSP
        void displayBalances() const {
            for (const auto& account : noWithdrawableAccount) {
                cout << "Balance of NoWithdrawableAccount: " << account->getBalance() << endl;
            }
            for(const auto & account : withdrawableAccounts){
                cout << "Balance of WithdrawableAccount: " << account->getBalance() << endl;
            }
        }

        // Methods to perform operations on accounts without violating LSP
        void makeDepositToNoWithdrawableAccounts(double amount) {
            for (auto& account : noWithdrawableAccount) {
                account->deposit(amount);
                cout << "Deposited " << amount << " to NoWithdrawableAccount. New Balance: " << account->getBalance() << endl;
            }
        }

        // Methods to perform operations on accounts without violating LSP
        void makeDepositToWithdrawableAccounts(double amount) {
            for (auto& account : withdrawableAccounts) {
                account->deposit(amount);
                cout << "Deposited " << amount << " to WithdrawableAccount. New Balance: " << account->getBalance() << endl;    
            }
        }

        // Methods to perform operations on accounts without violating LSP
        void makeWithdrawal(double amount) {
            for (auto& account : withdrawableAccounts) {
                account->withdraw(amount);
                cout << "Withdrew " << amount << " from WithdrawableAccount. New Balance: " << account->getBalance() << endl;
            }
        }

};


int main(){
    vector<NoWithdrawableAccount*> noWithdrawableAccounts;
    noWithdrawableAccounts.push_back(new FixedDepositAccount(3000));

    vector<WithdrawableAccount*> withdrawableAccounts;
    withdrawableAccounts.push_back((new SavingAccount(1000)));
    withdrawableAccounts.push_back((new CurrentAccount(2000)));

    Client client(noWithdrawableAccounts, withdrawableAccounts);
    client.displayBalances();
    client.makeDepositToNoWithdrawableAccounts(500);
    client.makeDepositToWithdrawableAccounts(500);
    client.makeWithdrawal(200);
    client.displayBalances();


    for (auto& account : noWithdrawableAccounts) {
        delete account;
    }
    for (auto& account : withdrawableAccounts) {
        delete account;
    }

    return 0;
}