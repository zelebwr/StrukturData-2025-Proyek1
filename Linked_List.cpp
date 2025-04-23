#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

struct Shirt {
    string id;
    string name;
    int attr_1; // price
    float attr_2; // rating
    Shirt* next;
};

void tambahShirt(Shirt*& head, const string& id, const string& name, int attr_1, float attr_2) {
    Shirt* baru = new Shirt{id, name, attr_1, attr_2, nullptr};
    if (!head) {
        head = baru;
        return;
    }
    Shirt* temp = head;
    while (temp->next) temp = temp->next;
    temp->next = baru;
}

bool dominates(Shirt* a, Shirt* b) {
    return (a->attr_1 <= b->attr_1 && a->attr_2 >= b->attr_2) &&
           (a->attr_1 < b->attr_1 || a->attr_2 > b->attr_2);
}

Shirt* skylineQuery(Shirt* head) {
    Shirt* skyline = nullptr;
    for (Shirt* s = head; s != nullptr; s = s->next) {
        bool isDominated = false;

        for (Shirt* sk = skyline; sk != nullptr; sk = sk->next) {
            if (dominates(sk, s)) {
                isDominated = true;
                break;
            }
        }

        if (!isDominated) {
            Shirt* newSkyline = nullptr;

            for (Shirt* sk = skyline; sk != nullptr; sk = sk->next) {
                if (!dominates(s, sk)) {
                    tambahShirt(newSkyline, sk->id, sk->name, sk->attr_1, sk->attr_2);
                }
            }

            tambahShirt(newSkyline, s->id, s->name, s->attr_1, s->attr_2);

            while (skyline) {
                Shirt* tmp = skyline;
                skyline = skyline->next;
                delete tmp;
            }

            skyline = newSkyline;
        }
    }

    return skyline;
}

Shirt* readCSV(const string& filename, int& count) {
    Shirt* head = nullptr;
    ifstream file(filename);
    string line;
    count = 0;

    if (!file.is_open()) {
        cerr << "Gagal membuka file: " << filename << endl;
        return head;
    }

    getline(file, line); // skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, nameStr, attr1Str, attr2Str;

        getline(ss, idStr, ',');
        getline(ss, nameStr, ',');
        getline(ss, attr1Str, ',');
        getline(ss, attr2Str, ',');

        if (attr1Str.empty() || attr2Str.empty()) continue;

        try {
            int attr1 = stoi(attr1Str);
            float attr2 = stof(attr2Str);
            tambahShirt(head, idStr, nameStr, attr1, attr2);
            count++;
        } catch (const invalid_argument& e) {
            cerr << "Baris tidak valid, dilewati: " << line << endl;
            continue;
        }
    }

    return head;
}

void bersihkan(Shirt*& head) {
    while (head) {
        Shirt* tmp = head;
        head = head->next;
        delete tmp;
    }
}

int main() {
    auto startAll = high_resolution_clock::now();

    int count = 0;
    auto startDataRetrieval = high_resolution_clock::now();
    Shirt* shirts = readCSV("ind_1000_2_product.csv", count);
    auto endDataRetrieval = high_resolution_clock::now();

    auto startPriceSkyline = high_resolution_clock::now();
    Shirt* minPrice = nullptr;
    for (Shirt* s = shirts; s != nullptr; s = s->next) {
        if (!minPrice || s->attr_1 < minPrice->attr_1)
            minPrice = s;
    }
    auto endPriceSkyline = high_resolution_clock::now();

    auto startRatingSkyline = high_resolution_clock::now();
    Shirt* maxRating = nullptr;
    for (Shirt* s = shirts; s != nullptr; s = s->next) {
        if (!maxRating || s->attr_2 > maxRating->attr_2)
            maxRating = s;
    }
    auto endRatingSkyline = high_resolution_clock::now();

    auto startTopSkyline = high_resolution_clock::now();
    Shirt* skyline = skylineQuery(shirts);
    auto endTopSkyline = high_resolution_clock::now();

    auto endAll = high_resolution_clock::now();

    cout << "Total Items: " << count << endl;

    cout << "\n=== Price Skyline (Lowest Price: " << minPrice->attr_1 << ") ===\n";
    cout << "1. Product: " << minPrice->name << " | Price: " << minPrice->attr_1 << " | Rating: " << minPrice->attr_2 << endl;

    cout << "\n=== Rating Skyline (Highest Rating: " << maxRating->attr_2 << ") ===\n";
    cout << "1. Product: " << maxRating->name << " | Price: " << maxRating->attr_1 << " | Rating: " << maxRating->attr_2 << endl;

    int skylineCount = 0;
    cout << "\n=== Top Skyline ===\n";
    for (Shirt* s = skyline; s != nullptr; s = s->next) {
        skylineCount++;
        cout << skylineCount << ". Product: " << s->name
             << " | Price: " << s->attr_1
             << " | Rating: " << s->attr_2 << endl;
    }

    duration<double> timeDataRetrieval = endDataRetrieval - startDataRetrieval;
    duration<double> timePriceSkyline = endPriceSkyline - startPriceSkyline;
    duration<double> timeRatingSkyline = endRatingSkyline - startRatingSkyline;
    duration<double> timeTopSkyline = endTopSkyline - startTopSkyline;
    duration<double> timeAll = endAll - startAll;

    cout << fixed << setprecision(6);
    cout << "\n=== Performance Measurement ===" << endl;
    cout << "Data Retrieval Time: " << timeDataRetrieval.count() << " seconds" << endl;
    cout << "Price Skyline Calculation Time: " << timePriceSkyline.count() << " seconds" << endl;
    cout << "Rating Skyline Calculation Time: " << timeRatingSkyline.count() << " seconds" << endl;
    cout << "Top Skyline Calculation Time: " << timeTopSkyline.count() << " seconds" << endl;
    cout << "Total Execution Time: " << timeAll.count() << " seconds" << endl;
    cout << "Total Memory Usage: " << (count * sizeof(Shirt)) << " bytes" << endl;

    bersihkan(shirts);
    bersihkan(skyline);

    return 0;
}