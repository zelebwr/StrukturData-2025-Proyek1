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

// Fungsi untuk membaca data dari file CSV dan mengembalikan map produk
std::map<std::string, Product> readCSV(const std::string& filename) {
    std::map<std::string, Product> products;
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

        // Parsing nilai-nilai dari satu baris
        std::getline(ss, p.id, ',');
        std::getline(ss, p.name, ',');
        std::getline(ss, token, ',');
        p.price = std::stod(token);
        std::getline(ss, token, ',');
        p.rating = std::stod(token);

        // Menyimpan produk ke dalam map dengan ID sebagai key
        products[p.id] = p;
    }

    return products;
}

// Fungsi untuk melakukan skyline query pada produk menggunakan std::map
std::map<std::string, Product> skylineQueryMap(const std::map<std::string, Product>& products) {
    std::map<std::string, Product> skyline;

    // Membandingkan tiap produk dengan produk lain untuk mengecek dominasi
    for (const auto& [id1, p1] : products) {
        bool dominated = false;
        for (const auto& [id2, p2] : products) {
            if (id1 == id2) continue;

            // Cek apakah produk p1 didominasi oleh p2
            if (p2.price <= p1.price && p2.rating >= p1.rating &&
                (p2.price < p1.price || p2.rating > p1.rating)) {
                dominated = true;
                break;
            }
        }
        // Jika tidak didominasi, masukkan ke dalam hasil skyline
        if (!dominated) {
            skyline[id1] = p1;
        }
    }

    return skyline;
}

int main() {
    std::string filename;
    std::cout << "Masukkan nama file CSV (harus berada dalam folder yang sama): ";
    std::getline(std::cin, filename);

    auto start_total = std::chrono::high_resolution_clock::now(); // Waktu mulai total

    auto start_retrieve = std::chrono::high_resolution_clock::now(); // Mulai waktu pengambilan data
    std::map<std::string, Product> products = readCSV(filename);
    auto end_retrieve = std::chrono::high_resolution_clock::now(); // Selesai pengambilan data
    std::chrono::duration<double> dataRetrievalTime = end_retrieve - start_retrieve;

    if (products.empty()) {
        std::cerr << "Tidak ada data yang diproses. Program dihentikan.\n";
        return 1;
    }

    auto start_price = std::chrono::high_resolution_clock::now(); // Mulai waktu skyline
    std::map<std::string, Product> bestProductMap = skylineQueryMap(products);
    auto end_price = std::chrono::high_resolution_clock::now(); // Selesai skyline
    std::chrono::duration<double> priceSkylineTime = end_price - start_price;

    auto start_top = std::chrono::high_resolution_clock::now(); // Mulai pencarian produk terbaik

    const Product* bestRating = nullptr;
    const Product* lowestPrice = nullptr;

    // Cari produk dengan rating tertinggi dan harga terendah dari hasil skyline
    for (const auto& [id, p] : bestProductMap) {
        if (!bestRating || p.rating > bestRating->rating) {
            bestRating = &p;
        }
        if (!lowestPrice || p.price < lowestPrice->price) {
            lowestPrice = &p;
        }
    }

    // Urutkan hasil skyline berdasarkan rating (desc), lalu harga (asc) dengan mengubah struktur data std::map menjadi std::vector
    std::vector<std::pair<std::string, Product>> sortedProducts(bestProductMap.begin(), bestProductMap.end());
    std::sort(sortedProducts.begin(), sortedProducts.end(), [](const auto& a, const auto& b) {
        if (a.second.rating == b.second.rating)
            return a.second.price < b.second.price;
        return a.second.rating > b.second.rating;
    });

    auto end_top = std::chrono::high_resolution_clock::now(); // Selesai pencarian terbaik
    std::chrono::duration<double> topSkylineTime = end_top - start_top;

    auto end_total = std::chrono::high_resolution_clock::now(); // Akhir dari semua proses
    std::chrono::duration<double> totalTime = end_total - start_total;

    // Tampilkan hasil skyline yang sudah diurutkan
    std::cout << "===============================\n";
    std::cout << " SKYLINE QUERY - PRODUK TERBAIK \n";
    std::cout << "===============================\n\n";

    for (const auto& [id, p] : sortedProducts) {
        std::cout << "- ID  : " << p.id << "\tNama  : " << p.name
                  << "\tHarga : " << p.price << "\tRating  : " << p.rating << "\n\n";
    }

    // Tampilkan produk terbaik berdasarkan kriteria tertentu
    std::cout << "===============================\n";
    std::cout << " Produk dengan Rating Tertinggi: " << bestRating->name << " (" << bestRating->rating << ")\n";
    std::cout << " Produk dengan Harga Termurah : " << lowestPrice->name << " (" << lowestPrice->price << ")\n";
    std::cout << "===============================\n";
    std::cout << "Waktu eksekusi skyline query: " << totalTime.count() << " detik\n";
    std::cout << "===============================\n";

    // Estimasi penggunaan memori
    size_t memoryUsage = sizeof(Product) * bestProductMap.size() + sizeof(std::map<std::string, Product>);
    std::cout << "\n=== Performance Measurement ===\n";
    std::cout << std::fixed << std::setprecision(7);
    std::cout << "Data Retrieval Time:             " << dataRetrievalTime.count() << " seconds\n";
    std::cout << "Price Skyline Calculation Time:  " << priceSkylineTime.count() << " seconds\n";
    std::cout << "Top Skyline Calculation Time:    " << topSkylineTime.count() << " seconds\n";
    std::cout << "Total Execution Time:            " << totalTime.count() << " seconds\n";
    std::cout << "Total Memory Usage:              " << memoryUsage << " bytes\n\n";

    return 0;
}
