#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <stack>

using namespace std;
using namespace std::chrono;

void quickSort(vector<int>& arr) {
    if (arr.empty())
        return;

    stack<pair<int, int>> s; //Store interval every sort
    s.push({0, (int)arr.size()-1});
    
    while (!s.empty()) {
        int low = s.top().first;
        int high = s.top().second;
        s.pop();
        
        if (low >= high)
            continue;

        int randomIndex = low + rand() % (high-low+1); //Random choose a pivot index
        swap(arr[randomIndex], arr[high]);
        
        // set pivot to last element of interval
        int pivot = arr[high];
        int i = low-1;
        for (int j=low; j<high; j++) {
            // put to left
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[high]);
        int pi = i+1;

        if (low < pi-1)
            s.push({low, pi-1});
        if (pi+1 < high)
            s.push({pi+1, high});
    }
}

int main() {
    // Initial random seed
    srand(time(NULL));

    ifstream file("data.csv");
    if (!file) {
        cout << "failed to open data.csv" << endl;
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
        if(!numbers.empty()){
            testData.push_back(numbers);
        }
    }
    
    file.close();
    
    int testCaseNumber = 1;
    long long total_time;
    for(auto &data : testData) {
        total_time = 0;
        cout << "Test Case " << testCaseNumber << ": include " << data.size() << " data" << endl;
        vector<int> sorted_data;
        for (int c=0; c<10; c++) {
            sorted_data = data;
            auto start = high_resolution_clock::now();
            quickSort(sorted_data);
            auto end = high_resolution_clock::now();
            auto durationStd = duration_cast<nanoseconds>(end - start);
            total_time += durationStd.count();
        }
        cout << "Quick Sort cost time: " << total_time/10 << " ns" << endl;
        
        cout << "The first 10 data: ";
        for (int i=0; i<min((int)sorted_data.size(), 10); i++) {
            cout << sorted_data[i] << " ";
        }
        cout << "\n\n";
        testCaseNumber++;
    }
    return 0;
}
