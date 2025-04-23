#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#endif

struct Point {
    int   id;     
    std::string label; 
    int   x;      
    int   y;      
};

bool dominates(const Point& a, const Point& b) {
    return (a.x <= b.x && a.y >= b.y)
        && (a.x <  b.x || a.y >  b.y);
}

struct Node {
    Point data;
    Node* next;
    Node(const Point& p): data(p), next(nullptr) {}
};

class Stack {
    Node* topNode;
  public:
    Stack(): topNode(nullptr) {}
    ~Stack() { while (topNode) pop(); }

    void push(const Point& p) {
        Node* n = new Node(p);
        n->next = topNode;
        topNode = n;
    }
    void pop() {
        if (!topNode) return;
        Node* tmp = topNode;
        topNode = topNode->next;
        delete tmp;
    }
    Point& peek() {
        if (!topNode) throw std::runtime_error("Stack kosong");
        return topNode->data;
    }
    bool isEmpty() const { return topNode == nullptr; }
};

size_t getMemoryUsageBytes() {
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
        return pmc.WorkingSetSize;
#endif
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc!=2) {
        std::cerr<<"Usage: "<<argv[0]<<" <path_to_csv>\n";
        return 1;
    }

    using clk = std::chrono::high_resolution_clock;
    auto t_start = clk::now();

    auto t_read0 = clk::now();
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr<<"Gagal membuka file: "<<argv[1]<<"\n";
        return 1;
    }
    std::string line;
    std::getline(infile, line); 
    std::vector<Point> pts;
    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string sid, lbl, sx, sy;
        std::getline(ss, sid, ',');
        std::getline(ss, lbl, ',');
        std::getline(ss, sx, ',');
        std::getline(ss, sy);
        pts.push_back({ std::stoi(sid), lbl,
                        std::stoi(sx), std::stoi(sy) });
    }
    infile.close();
    auto t_read1 = clk::now();

    auto t_sort0 = clk::now();
    std::sort(pts.begin(), pts.end(), [](auto& a, auto& b){
        if (a.x!=b.x) return a.x<b.x;
        return a.y>b.y;
    });
    auto t_sort1 = clk::now();

    auto t_sky0 = clk::now();
    Stack stk;
    for (auto& p: pts) {
        
        while (!stk.isEmpty() && dominates(p, stk.peek()))
            stk.pop();
        
        if (!stk.isEmpty() && dominates(stk.peek(), p))
            continue;
        stk.push(p);
    }
    auto t_sky1 = clk::now();

    std::vector<Point> sky;
    while (!stk.isEmpty()) {
        sky.push_back(stk.peek());
        stk.pop();
    }
    std::reverse(sky.begin(), sky.end());
    auto t_end = clk::now();

    double dt_read  = std::chrono::duration<double>(t_read1 - t_read0).count();
    double dt_sort  = std::chrono::duration<double>(t_sort1 - t_sort0).count();
    double dt_sky   = std::chrono::duration<double>(t_sky1   - t_sky0  ).count();
    double dt_total = std::chrono::duration<double>(t_end    - t_start).count();

    std::cout<<std::fixed<<std::setprecision(6);
    std::cout<<"Data retrieval time        : "<<dt_read  <<" detik\n";
    std::cout<<"Sorting time               : "<<dt_sort  <<" detik\n";
    std::cout<<"Skyline calc. time         : "<<dt_sky   <<" detik\n";
    std::cout<<"Total execution time       : "<<dt_total <<" detik\n";
    double memMB = getMemoryUsageBytes()/(1024.0*1024.0);
    std::cout<<std::setprecision(3)
             <<"Total memory usage         : "<<memMB<<" MB\n\n";

    std::cout<<"Skyline points ("<<sky.size()<<"):\n";
    for (auto& p: sky) {
        std::cout
          << "id="<<p.id
          << ", label="<<p.label
          << ", price="<<p.x
          << ", rating="<<p.y<<"\n";
    }

    return 0;
}
