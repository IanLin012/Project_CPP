#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i <n-1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    ifstream file("data.csv");
    if (!file) {
        cout << "unable to open data.csv" << endl;
        return 1;
    }

    string line;
    vector<vector<int>> testData;
    
    while(getline(file, line)) {
        vector<int> numbers;
        stringstream ss(line);
        string value;

        while(getline(ss, value, ',')) {
            numbers.push_back(stoi(value));
        }
        testData.push_back(numbers);
    }
    
    file.close();

    int testCaseNumber = 1;
    long long total_time;
    for(auto &data : testData) {
        total_time = 0;
        cout << "Test Case " << testCaseNumber << ": include " << data.size() << " data" << endl;
        for (int c=0; c<3; c++) {
            auto start = high_resolution_clock::now();
            bubbleSort(data);
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            total_time += duration.count();
        }
        cout << "bubble sort cost time: " << total_time/3 << " ns" << endl;

        cout << "10 data after sort: ";
        for (int i = 0; i < min((int)data.size(), 10); i++) {
            cout << data[i] << " ";
        }
        cout << "\n\n";
        testCaseNumber++;
    }
    return 0;
}
