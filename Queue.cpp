#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
using namespace std;

bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

bool dominates(int hargaA, int ratingA, int hargaB, int ratingB) {
    return (hargaA <= hargaB && ratingA >= ratingB) &&
           (hargaA < hargaB || ratingA > ratingB);
}

int main() {
    queue<vector<string>> dataQueue;
    vector<vector<string>> skyline;

    ifstream file("ind_1000_2_product.csv");
    if (!file.is_open()) {
        cerr << "Error: Gagal membuka file.\n";
        return 1;
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> produk;
        string temp;

        while (getline(ss, temp, ',')) {
            produk.push_back(temp);
        }

        if (produk.size() == 4 && isNumber(produk[2]) && isNumber(produk[3])) {
            dataQueue.push(produk);
        }
    }
    file.close();

    auto start = chrono::high_resolution_clock::now();

    while (!dataQueue.empty()) {
        auto kandidat = dataQueue.front();
        dataQueue.pop();

        int hargaK = stoi(kandidat[2]);
        int ratingK = stoi(kandidat[3]);
        bool isSkyline = true;

        for (const auto& s : skyline) {
            int hargaS = stoi(s[2]);
            int ratingS = stoi(s[3]);

            if (dominates(hargaS, ratingS, hargaK, ratingK)) {
                isSkyline = false;
                break;
            }
        }

        if (isSkyline) {
            vector<vector<string>> newSkyline;
            for (const auto& s : skyline) {
                int hargaS = stoi(s[2]);
                int ratingS = stoi(s[3]);

                if (!dominates(hargaK, ratingK, hargaS, ratingS)) {
                    newSkyline.push_back(s);
                }
            }
            newSkyline.push_back(kandidat);
            skyline = newSkyline;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    const string BLUE1 = "\033[38;5;33m";   
    const string BLUE2 = "\033[38;5;38m";   
    const string BLUE3 = "\033[38;5;44m";   
    const string BLUE4 = "\033[38;5;49m";   
    const string BLUE5 = "\033[38;5;63m";   
    const string RESET = "\033[0m";

    cout << "==========================================================\n";
    cout << BLUE1 << "    __  __           _ __   _____ __         ___          " << RESET << endl;
    cout << BLUE2 << "   / / / /___ ______(_) /  / ___// /____  __/ (_)___  ___ " << RESET << endl;
    cout << BLUE3 << "  / /_/ / __ `/ ___/ / /   \\__ \\/ //_/ / / / / / __ \\/ _ \\ " << RESET << endl;
    cout << BLUE4 << " / __  / /_/ / (__  ) / /   ___/ / ,< / /_/ / / / / /  __/ " << RESET << endl;
    cout << BLUE5 << "/_/ /_/\\__,_/____/_/_/   /____/_/|_|\\__, /_/_/_/ /_/\\___/  " << RESET << endl;
    cout << BLUE1 << "                                   /____/                  " << RESET << endl;
    cout << "==========================================================\n";
    cout << "Skyline Produk: " << skyline.size() << " produk\n";
    cout << "----------------------------------------------------------\n";
    cout << "ID\tProduk\t\tHarga\tRating\n";
    cout << "----------------------------------------------------------\n";

    for (const auto& p : skyline) {
        cout << p[0] << "\t" << p[1];
        if (p[1].length() < 8) cout << "\t";
        cout << "\t" << p[2] << "\t" << p[3] << "\n";
    }

    cout << "\nWaktu eksekusi: " << duration.count() << " detik\n";
    cout << "==========================================================\n";

    return 0;
}
