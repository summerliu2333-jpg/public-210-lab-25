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

    ifstream fin(filename);
    auto start = high_resolution_clock::now();
    while (fin >> code) {
        vec.push_back(code);
    }
    fin.close();
    auto end = high_resolution_clock::now();
    long long vec_time = duration_cast<nanoseconds>(end - start).count();

    fin.open(filename);
    start = high_resolution_clock::now();
    while (fin >> code) {
        lst.push_back(code);
    }
    fin.close();
    end = high_resolution_clock::now();
    long long lst_time = duration_cast<nanoseconds>(end - start).count();

    fin.open(filename);
    start = high_resolution_clock::now();
    while (fin >> code) {
        st.insert(code);
    }
    fin.close();
    end = high_resolution_clock::now();
    long long st_time = duration_cast<nanoseconds>(end - start).count();

    return {"Read", vec_time, lst_time, st_time};
}

TimingResult runSortTest(vector<string>& vec, list<string>& lst, set<string>& st) {
    auto start = high_resolution_clock::now();
    sort(vec.begin(), vec.end());
    auto end = high_resolution_clock::now();
    long long vec_time = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    lst.sort();
    end = high_resolution_clock::now();
    long long lst_time = duration_cast<nanoseconds>(end - start).count();

    return {"Sort", vec_time, lst_time, -1};
}

TimingResult runInsertTest(vector<string>& vec, list<string>& lst, set<string>& st) {
    const string insert_val = "TESTCODE";

    auto vec_it = vec.begin() + vec.size() / 2;
    auto start = high_resolution_clock::now();
    vec.insert(vec_it, insert_val);
    auto end = high_resolution_clock::now();
    long long vec_time = duration_cast<nanoseconds>(end - start).count();

    auto lst_it = lst.begin();
    advance(lst_it, lst.size() / 2);
    start = high_resolution_clock::now();
    lst.insert(lst_it, insert_val);
    end = high_resolution_clock::now();
    long long lst_time = duration_cast<nanoseconds>(end - start).count();

    start = high_resolution_clock::now();
    st.insert(insert_val);
    end = high_resolution_clock::now();
    long long st_time = duration_cast<nanoseconds>(end - start).count();

    return {"Insert", vec_time, lst_time, st_time};
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

    TimingResult sort_res = runSortTest(vec, lst, st);
    results.push_back(sort_res);

    TimingResult insert_res = runInsertTest(vec, lst, st);
    results.push_back(insert_res);

    printResults(results);

    return 0;
}