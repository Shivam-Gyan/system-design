#include<iostream>
#include<bits/stdc++.h>
using namespace std;



class Product{
    private:
        string name;
        double price;

    public:
        Product(const string& name, double price)
            : name(name), price(price) {}

        string getName() const {
            return name;
        }

        double getPrice() const {
            return price;
        }
};


//  abstract class for discount strategy, we can add new discount types without changing the shopping cart class

class Discount{
    public:
        virtual double apply(double total) const = 0; // Pure virtual function
        virtual ~Discount() = default; // Virtual destructor
};


// Concrete discount strategies
class NoDiscount: public Discount{

    public:
        double apply(double total) const override{
            return total; // No discount applied
        }
};

// Example of a percentage discount strategy
class PercentageDiscount: public Discount{
    private:
        double percentage;

    public:
        PercentageDiscount(double percentage) : percentage(percentage) {}

        double apply(double total) const override {
            return total * (1 - percentage / 100); // Apply percentage discount
        }
};

// Example of a flat discount strategy

class FlatDiscount: public Discount{
    private:
    double amount;

    public:
        FlatDiscount(double amount ) : amount(amount) {}

        double apply(double total) const override{
            return max(0.0, total - amount); // Apply flat discount, ensuring total doesn't go negative
        }
};



class ShoppingCart {
    private:
        vector<Product> products;
        Discount* discount;

    public:
        ShoppingCart(Discount* discount): discount(discount) {}

        void addProduct(const Product& product) {
            products.push_back(product);
        }

        const vector<Product>& getProducts() const {
            return products;
        }

        double calculateTotal() const {
            double total = 0.0;
            for (const auto& product : products) {
                total += product.getPrice();
            }

            //  we dont need to change this method when we add new discount types, we just need to create new discount class and pass it to the shopping cart
            return discount->apply(total);
        }
};


int main(){

    // Create discount strategy
    Discount* discount = new PercentageDiscount(10); // 10% discount

    // Create shopping cart with the discount strategy
    ShoppingCart cart(discount);

    // Add products to the cart
    cart.addProduct(Product("Laptop", 1000.0));
    cart.addProduct(Product("Smartphone", 500.0));

    cout << "Total price: $" << cart.calculateTotal() << endl;


    delete discount; // Clean up the dynamically allocated discount object
    return 0;
}