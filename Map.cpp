#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <map>

// Struktur data untuk menyimpan informasi produk
struct Product {
    std::string id;
    std::string name;
    double price;
    double rating;
};

// Fungsi untuk membaca data dari file CSV dan mengembalikan vector produk
std::vector<Product> readCSV(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "[ERROR] Gagal membuka file. Pastikan file berada dalam direktori yang sama dengan program.\n";
        return products;
    }

    // Melewati baris header
    std::getline(file, line);

    // Membaca tiap baris data produk
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Product p;

        std::getline(ss, p.id, ',');
        std::getline(ss, p.name, ',');
        std::getline(ss, token, ',');
        p.price = std::stod(token);
        std::getline(ss, token, ',');
        p.rating = std::stod(token);

        products.push_back(p);
    }

    return products;
}

// Fungsi untuk melakukan skyline query menggunakan full std::map, input/output berupa vector
std::vector<Product> skylineQueryMapOnly(const std::vector<Product>& inputProducts) {
    std::map<double, std::vector<Product>> priceMap;

    for (const Product& p : inputProducts) {
        priceMap[p.price].push_back(p);
    }

    std::map<std::string, Product> skyline;
    double maxRatingSoFar = -1.0;

    for (const auto& [price, productList] : priceMap) {
        for (const Product& p : productList) {
            if (p.rating > maxRatingSoFar) {
                skyline[p.id] = p;
                maxRatingSoFar = p.rating;
            }
        }
    }

    std::vector<Product> result;
    for (const auto& [id, p] : skyline) {
        result.push_back(p);
    }

    return result;
}

int main() {
    std::string filename;
    std::cout << "Masukkan nama file CSV (harus berada dalam folder yang sama): ";
    std::getline(std::cin, filename);

    auto start_total = std::chrono::high_resolution_clock::now();

    auto start_retrieve = std::chrono::high_resolution_clock::now();
    std::vector<Product> products = readCSV(filename);
    auto end_retrieve = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> dataRetrievalTime = end_retrieve - start_retrieve;

    if (products.empty()) {
        std::cerr << "Tidak ada data yang diproses. Program dihentikan.\n";
        return 1;
    }

    auto start_price = std::chrono::high_resolution_clock::now();
    std::vector<Product> skylineProducts = skylineQueryMapOnly(products);
    auto end_price = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> priceSkylineTime = end_price - start_price;

    auto start_top = std::chrono::high_resolution_clock::now();

    const Product* bestRating = nullptr;
    const Product* lowestPrice = nullptr;

    for (const auto& p : skylineProducts) {
        if (!bestRating || p.rating > bestRating->rating) {
            bestRating = &p;
        }
        if (!lowestPrice || p.price < lowestPrice->price) {
            lowestPrice = &p;
        }
    }

    std::sort(skylineProducts.begin(), skylineProducts.end(), [](const Product& a, const Product& b) {
        if (a.rating == b.rating)
            return a.price < b.price;
        return a.rating > b.rating;
    });

    auto end_top = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> topSkylineTime = end_top - start_top;

    auto end_total = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = end_total - start_total;

    std::cout << "===============================\n";
    std::cout << " SKYLINE QUERY - PRODUK TERBAIK \n";
    std::cout << "===============================\n\n";

    for (const auto& p : skylineProducts) {
        std::cout << "- ID  : " << p.id << "\tNama  : " << p.name
                  << "\tHarga : " << p.price << "\tRating  : " << p.rating << "\n\n";
    }

    std::cout << "===============================\n";
    std::cout << " Produk dengan Rating Tertinggi: " << bestRating->name << " (" << bestRating->rating << ")\n";
    std::cout << " Produk dengan Harga Termurah : " << lowestPrice->name << " (" << lowestPrice->price << ")\n";
    std::cout << "===============================\n";
    std::cout << "Waktu eksekusi skyline query: " << totalTime.count() << " detik\n";
    std::cout << "===============================\n";

    size_t memoryUsage = sizeof(Product) * skylineProducts.size() + sizeof(std::map<double, std::vector<Product>>) + sizeof(std::map<std::string, Product>);
    std::cout << "\n=== Performance Measurement ===\n";
    std::cout << std::fixed << std::setprecision(7);
    std::cout << "Data Retrieval Time:             " << dataRetrievalTime.count() << " seconds\n";
    std::cout << "Price Skyline Calculation Time:  " << priceSkylineTime.count() << " seconds\n";
    std::cout << "Top Skyline Calculation Time:    " << topSkylineTime.count() << " seconds\n";
    std::cout << "Total Execution Time:            " << totalTime.count() << " seconds\n";
    std::cout << "Total Memory Usage:              " << memoryUsage << " bytes\n\n";

    return 0;
}
