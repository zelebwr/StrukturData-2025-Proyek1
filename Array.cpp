#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

struct Product {
    int id;
    int price;
    int rating;
};

vector<Product> readProductsFromCSV(const string &filename) {
    vector<Product> products;
    ifstream file(filename);
    string line, cell;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return products;
    }

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string label;
        int id, price, rating;

        getline(ss, cell, ','); id = stoi(cell);
        getline(ss, label, ','); // skip label
        getline(ss, cell, ','); price = stoi(cell);
        getline(ss, cell, ','); rating = stoi(cell);

        products.push_back({id, price, rating});
    }

    return products;
}

bool dominates(const Product &a, const Product &b) {
    return (a.price <= b.price && a.rating >= b.rating) &&
           (a.price < b.price || a.rating > b.rating);
}

vector<Product> computeSkyline(const vector<Product> &products) {
    vector<Product> skyline;

    for (const auto &p : products) {
        bool dominated = false;
        for (const auto &q : products) {
            if (dominates(q, p)) {
                dominated = true;
                break;
            }
        }
        if (!dominated) {
            skyline.push_back(p);
        }
    }

    return skyline;
}

int main() {
    auto start = high_resolution_clock::now();

    auto retrieval_start = high_resolution_clock::now();
    vector<Product> products = readProductsFromCSV("ind_1000_2_product.csv");
    auto retrieval_end = high_resolution_clock::now();
    double retrieval_time = duration<double>(retrieval_end - retrieval_start).count();

    if (products.empty()) {
        cerr << "No products loaded. Exiting.\n";
        return 1;
    }

    auto skyline_start = high_resolution_clock::now();
    vector<Product> skyline = computeSkyline(products);
    auto skyline_end = high_resolution_clock::now();
    double skyline_time = duration<double>(skyline_end - skyline_start).count();

    auto stop = high_resolution_clock::now();
    double total_time = duration<double>(stop - start).count();

    size_t memory_usage = sizeof(Product) * (products.size() + skyline.size());

    // Output
    cout << "=== Skyline Products ===\n";
    for (size_t i = 0; i < skyline.size(); ++i) {
        cout << i + 1 << ". Product: product-" << skyline[i].id
             << " | Price: " << skyline[i].price
             << " | Rating: " << skyline[i].rating << endl;
    }

    cout << fixed << setprecision(6);
    cout << "\n=== Performance Measurement ===\n";
    cout << "Data Retrieval Time: " << retrieval_time << " seconds\n";
    cout << "Skyline Calculation Time: " << skyline_time << " seconds\n";
    cout << "Total Execution Time: " << total_time << " seconds\n";
    cout << "Total Memory Usage: " << memory_usage << " bytes\n";

    return 0;
}
