#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
    =========================
    Product Class
    Responsibility:
    - Represents product data only
    - Reason to change: product structure changes
    =========================
*/
class Product {
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


/*
    =========================
    ShoppingCart Class
    Responsibility:
    - Manage cart state
    - Add/remove products
    - Calculate total
    - Reason to change: cart business logic changes
    =========================
*/
class ShoppingCart {
private:
    vector<Product> products;  // Encapsulated

public:
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
        return total;
    }
};


/*
    =========================
    InvoiceGenerator Class
    Responsibility:
    - Generate invoice data (not printing)
    - Reason to change: invoice formatting changes
    =========================
*/
class InvoiceGenerator {
public:
    string generate(const ShoppingCart& cart) const {
        string invoice = "\n===== Invoice =====\n";

        for (const auto& product : cart.getProducts()) {
            invoice += product.getName() + " : " 
                     + to_string(product.getPrice()) + "\n";
        }

        invoice += "-------------------\n";
        invoice += "Total: " + to_string(cart.calculateTotal()) + "\n";

        return invoice;
    }
};


/*
    =========================
    PaymentProcessor Class
    Responsibility:
    - Handle payment processing
    - Reason to change: payment logic changes
    =========================
*/
class PaymentProcessor {
public:
    void processPayment(const ShoppingCart& cart) const {
        double total = cart.calculateTotal();
        cout << "\nProcessing payment of amount: " << total << endl;

        // Payment gateway logic would go here
    }
};


/*
    =========================
    InvoicePrinter Class
    Responsibility:
    - Handle output/printing
    - Reason to change: output medium changes
    =========================
*/
class InvoicePrinter {
public:
    void print(const string& invoiceData) const {
        cout << invoiceData << endl;
    }
};


/*
    =========================
    Main Function
    =========================
*/
int main() {

    // Create products (no raw pointers needed)
    Product laptop("Laptop", 1000.0);
    Product smartphone("Smartphone", 500.0);

    // Create shopping cart
    ShoppingCart cart;
    cart.addProduct(laptop);
    cart.addProduct(smartphone);

    // Process payment
    PaymentProcessor paymentProcessor;
    paymentProcessor.processPayment(cart);

    // Generate invoice
    InvoiceGenerator invoiceGenerator;
    string invoiceData = invoiceGenerator.generate(cart);

    // Print invoice
    InvoicePrinter printer;
    printer.print(invoiceData);

    return 0;
}
