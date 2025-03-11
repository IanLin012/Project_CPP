#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
        vector<int> originalData = data;
        for (int c=0; c<100; c++) {
            vector<int> temp = originalData;
            auto start = high_resolution_clock::now();
            sort(temp.begin(), temp.end());
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(end - start);
            total_time += duration.count();
            if(c == 0) {
                data = temp;
            }
        }
        cout << "std::sort cost time: " << total_time/100 << " ns" << endl;

        cout << "10 data after sort: ";
        for (int i = 0; i < min((int)data.size(), 10); i++) {
            cout << data[i] << " ";
        }
        cout << "\n\n";
        testCaseNumber++;
    }
    return 0;
}
