#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include <chrono>
#include <climits>
using namespace std;

bool isNumber(const string& s) {
    for (char c : s) if (!isdigit(c)) return false;
    return !s.empty();
}

bool dominates(int priceA, int ratingA, int priceB, int ratingB) {
    return (priceA <= priceB && ratingA >= ratingB) && (priceA < priceB || ratingA > ratingB);
}

size_t getMemoryUsageKB() {
    string line;
    ifstream procStatus("/proc/self/status");
    while (getline(procStatus, line)) {
        if (line.substr(0, 6) == "VmRSS:") {
            stringstream ss(line);
            string key, value, unit;
            ss >> key >> value >> unit;
            return stoi(value); // dalam KB
        }
    }
    return 0;
}

int main() {
    queue<vector<string>> dataQueue;
    vector<vector<string>> skyline;
    auto totalStart = chrono::high_resolution_clock::now();

    auto dataRetrievalStart = chrono::high_resolution_clock::now();
    ifstream file("ind_1000_2_product.csv");
    if (!file.is_open()) {
        cerr << "Error: Failed to open the file.\n";
        return 1;
    }
    string line;
    getline(file, line); // Skip header
    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> p;
        string tmp;
        while (getline(ss, tmp, ',')) p.push_back(tmp);
        if (p.size() == 4 && isNumber(p[2]) && isNumber(p[3])) dataQueue.push(p);
    }
    file.close();
    auto dataRetrievalEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> dataRetrievalDuration = dataRetrievalEnd - dataRetrievalStart;

    auto skylineCalculationStart = chrono::high_resolution_clock::now();
    while (!dataQueue.empty()) {
        auto c = dataQueue.front();
        dataQueue.pop();
        int pC = stoi(c[2]), rC = stoi(c[3]);
        bool ok = true;
        for (auto &s : skyline) {
            int pS = stoi(s[2]), rS = stoi(s[3]);
            if (dominates(pS, rS, pC, rC)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            vector<vector<string>> tmp;
            for (auto &s : skyline) {
                int pS = stoi(s[2]), rS = stoi(s[3]);
                if (!dominates(pC, rC, pS, rS)) tmp.push_back(s);
            }
            tmp.push_back(c);
            skyline.swap(tmp);
        }
    }
    auto skylineCalculationEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> skylineCalculationDuration = skylineCalculationEnd - skylineCalculationStart;

    int highestRating = INT_MIN;
    vector<string> best;
    int lowestPrice = INT_MAX;
    vector<string> cheap;
    for (auto &p : skyline) {
        int price = stoi(p[2]), rating = stoi(p[3]);
        if (rating > highestRating) {
            highestRating = rating;
            best = p;
        }
        if (price < lowestPrice) {
            lowestPrice = price;
            cheap = p;
        }
    }

    auto displayStart = chrono::high_resolution_clock::now();
    const string B1 = "\033[38;5;33m", B2 = "\033[38;5;38m", B3 = "\033[38;5;44m", B4 = "\033[38;5;49m", B5 = "\033[38;5;63m", R = "\033[0m";
    cout << "==========================================================\n";
    cout << B1 << "    __  __           _ __   _____ __         ___           " << R << "\n";
    cout << B2 << "   / / / /___ ______(_) /  / ___// /____  __/ (_)___  ___  " << R << "\n";
    cout << B3 << "  / /_/ / __ `/ ___/ / /   \\__ \\/  /_/ / / / / / __ \\/ _ \\" << R << "\n";
    cout << B4 << " / __  / /_/ (__  ) / /   ___/ / ,< / /_/ / / / / / /  __/ " << R << "\n";
    cout << B5 << "/_/ /_/\\__,_/____/_/_/   /____/_/|_|\\__, /_/_/_/ /_/\\___/  " << R << "\n";
    cout << B1 << "                                   /____/                  " << R << "\n";
    cout << "==========================================================\n";
    cout << "Skyline Products: " << skyline.size() << " products\n";
    cout << "----------------------------------------------------------\n";
    cout << "ID\tProduct\t\tPrice\tRating\n";
    cout << "----------------------------------------------------------\n";
    for (auto &p : skyline) cout << p[0] << "\t" << p[1] << (p[1].length() < 8 ? "\t" : "") << "\t" << p[2] << "\t" << p[3] << "\n";
    auto displayEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> displayDuration = displayEnd - displayStart;

    auto totalEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> totalDuration = totalEnd - totalStart;

    cout << "==========================================================\n";
    cout << "Performance Measurement\n";
    cout << "----------------------------------------------------------\n";
    cout << "Data Retrieval Time: " << dataRetrievalDuration.count() << " seconds\n";
    cout << "Skyline Calculation Time: " << skylineCalculationDuration.count() << " seconds\n";
    cout << "Display Time: " << displayDuration.count() << " seconds\n";
    cout << "Total Execution Time: " << totalDuration.count() << " seconds\n";
    cout << "Memory Usage: " << getMemoryUsageKB() << " KB\n";  // Memori usage di sini
    cout << "==========================================================\n";
    cout << "Highest Rating Product:\n";
    cout << "----------------------------------------------------------\n";
    cout << best[0] << "\t" << best[1] << (best[1].length() < 8 ? "\t" : "") << "\t" << best[2] << "\t" << best[3] << "\n";
    cout << "==========================================================\n";
    cout << "Lowest Price Product:\n";
    cout << "----------------------------------------------------------\n";
    cout << cheap[0] << "\t" << cheap[1] << (cheap[1].length() < 8 ? "\t" : "") << "\t" << cheap[2] << "\t" << cheap[3] << "\n";
    cout << "==========================================================\n";
    return 0;
}
