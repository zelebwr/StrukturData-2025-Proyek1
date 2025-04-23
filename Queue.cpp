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
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

bool dominates(int priceA, int ratingA, int priceB, int ratingB) {
    return (priceA <= priceB && ratingA >= ratingB) &&
           (priceA < priceB || ratingA > ratingB);
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
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        vector<string> product;
        string temp;
        while (getline(ss, temp, ',')) {
            product.push_back(temp);
        }
        if (product.size() == 4 && isNumber(product[2]) && isNumber(product[3])) {
            dataQueue.push(product);
        }
    }
    file.close();
    auto dataRetrievalEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> dataRetrievalDuration = dataRetrievalEnd - dataRetrievalStart;

    auto ratingSkylineStart = chrono::high_resolution_clock::now();
    while (!dataQueue.empty()) {
        auto candidate = dataQueue.front();
        dataQueue.pop();

        int priceK = stoi(candidate[2]);
        int ratingK = stoi(candidate[3]);
        bool isSkyline = true;

        for (const auto& s : skyline) {
            int priceS = stoi(s[2]);
            int ratingS = stoi(s[3]);

            if (dominates(priceS, ratingS, priceK, ratingK)) {
                isSkyline = false;
                break;
            }
        }

        if (isSkyline) {
            vector<vector<string>> newSkyline;
            for (const auto& s : skyline) {
                int priceS = stoi(s[2]);
                int ratingS = stoi(s[3]);

                if (!dominates(priceK, ratingK, priceS, ratingS)) {
                    newSkyline.push_back(s);
                }
            }
            newSkyline.push_back(candidate);
            skyline = newSkyline;
        }
    }
    auto ratingSkylineEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> ratingSkylineDuration = ratingSkylineEnd - ratingSkylineStart;

    auto priceSkylineStart = chrono::high_resolution_clock::now();
    int highestRating = INT_MIN;
    vector<string> highestRatingRow;
    int lowestPrice = INT_MAX;
    vector<string> lowestPriceRow;

    for (const auto& p : skyline) {
        int price = stoi(p[2]);
        int rating = stoi(p[3]);

        if (rating > highestRating) {
            highestRating = rating;
            highestRatingRow = p;
        }
        if (price < lowestPrice) {
            lowestPrice = price;
            lowestPriceRow = p;
        }
    }
    auto priceSkylineEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> priceSkylineDuration = priceSkylineEnd - priceSkylineStart;

    auto topSkylineStart = chrono::high_resolution_clock::now();

    const string BLUE1 = "\033[38;5;33m";   
    const string BLUE2 = "\033[38;5;38m";   
    const string BLUE3 = "\033[38;5;44m";   
    const string BLUE4 = "\033[38;5;49m";   
    const string BLUE5 = "\033[38;5;63m";   
    const string RESET = "\033[0m";
    cout << "==========================================================\n";
    cout << BLUE1 << "    __  __           _ __   _____ __         ___           " << RESET << endl;
    cout << BLUE2 << "   / / / /___ ______(_) /  / ___// /____  __/ (_)___  ___  " << RESET << endl;
    cout << BLUE3 << "  / /_/ / __ `/ ___/ / /   \\__ \\/  /_/ / / / / / __ \\/ _ \\ " << RESET << endl;
    cout << BLUE4 << " / __  / /_/ (__  ) / /   ___/ / ,< / /_/ / / / / / /  __/ " << RESET << endl;
    cout << BLUE5 << "/_/ /_/\\__,_/____/_/_/   /____/_/|_|\\__, /_/_/_/ /_/\\___/  " << RESET << endl;
    cout << BLUE1 << "                                   /____/                  " << RESET << endl;
    cout << "==========================================================\n";
    cout << "Skyline Products: " << skyline.size() << " products\n";
    cout << "----------------------------------------------------------\n";
    cout << "ID\tProduct\t\tPrice\tRating\n";
    cout << "----------------------------------------------------------\n";

    for (const auto& p : skyline) {
        cout << p[0] << "\t" << p[1];
        if (p[1].length() < 8) cout << "\t";
        cout << "\t" << p[2] << "\t" << p[3] << "\n";
    }

    auto topSkylineEnd = chrono::high_resolution_clock::now();
    chrono::duration<double> topSkylineDuration = topSkylineEnd - topSkylineStart;

    auto totalEnd = chrono::high_resolution_clock::now(); 
    chrono::duration<double> totalDuration = totalEnd - totalStart;

    cout << "==========================================================\n";
    cout << "Performance Measurement\n";
    cout << "----------------------------------------------------------\n";
    cout << "Data Retrieval Time: " << dataRetrievalDuration.count() << " seconds\n";
    cout << "Price Skyline Calculation Time: " << priceSkylineDuration.count() << " seconds\n";
    cout << "Rating Skyline Calculation Time: " << ratingSkylineDuration.count() << " seconds\n";
    cout << "Top Skyline Calculation Time: " << topSkylineDuration.count() << " seconds\n";
    cout << "Total Execution Time: " << totalDuration.count() << " seconds\n";
    cout << "==========================================================\n";    
    cout << "Highest Rating Product:\n";
    cout << "----------------------------------------------------------\n";
    cout << "ID\tProduct\t\tPrice\tRating\n";
    cout << "----------------------------------------------------------\n";
    cout << highestRatingRow[0] << "\t" << highestRatingRow[1];
    if (highestRatingRow[1].length() < 8) cout << "\t";
    cout << "\t" << highestRatingRow[2] << "\t" << highestRatingRow[3] << "\n";
    cout << "==========================================================\n";
    cout << "Lowest Price Product:\n";
    cout << "----------------------------------------------------------\n";
    cout << "ID\tProduct\t\tPrice\tRating\n";
    cout << "----------------------------------------------------------\n";
    cout << lowestPriceRow[0] << "\t" << lowestPriceRow[1];
    if (lowestPriceRow[1].length() < 8) cout << "\t";
    cout << "\t" << lowestPriceRow[2] << "\t" << lowestPriceRow[3] << "\n";
    cout << "==========================================================\n";

    return 0;
}
