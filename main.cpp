//COMSC-210-5068, lab 25, Yang Liu
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <list>
#include <set>

using namespace std;
using namespace chrono;

struct TimingResult {
    string operation;
    long long vector_time;
    long long list_time;
    long long set_time;
};

TimingResult runReadTest(const string& filename) {
    vector<string> vec;
    list<string> lst;
    set<string> st;
    string code;

    auto start = high_resolution_clock::now();
    ifstream fin(filename);
    while (fin >> code) {
        vec.push_back(code);
    }
    fin.close();
    auto end = high_resolution_clock::now();
    long long vec_time = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    fin.open(filename);
    while (fin >> code) {
        lst.push_back(code);
    }
    fin.close();
    end = high_resolution_clock::now();
    long long lst_time = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    fin.open(filename);
    while (fin >> code) {
        st.insert(code);
    }
    fin.close();
    end = high_resolution_clock::now();
    long long st_time = duration_cast<nanoseconds>(end - start).count();

    return {"Read", vec_time, lst_time, st_time};
}

void printResults(const vector<TimingResult>& results) {
    cout << right << setw(12) << "Operation"
         << setw(10) << "Vector"
         << setw(10) << "List"
         << setw(10) << "Set" << endl;

    for (const auto& res : results) {
        cout << right << setw(12) << res.operation;
        
        if (res.vector_time == -1)
            cout << setw(10) << "-1";
        else
            cout << setw(10) << res.vector_time;

        if (res.list_time == -1)
            cout << setw(10) << "-1";
        else
            cout << setw(10) << res.list_time;

        if (res.set_time == -1)
            cout << setw(10) << "-1";
        else
            cout << setw(10) << res.set_time;

        cout << endl;
    }
}

int main() {
    const string data_file = "codes.txt";
    vector<TimingResult> results;

    TimingResult read_res = runReadTest(data_file);
    results.push_back(read_res);

    vector<string> vec;
    list<string> lst;
    set<string> st;
    string code;
    ifstream fin(data_file);
    while (fin >> code) {
        vec.push_back(code);
        lst.push_back(code);
        st.insert(code);
    }
    fin.close();

    printResults(results);

    return 0;
}