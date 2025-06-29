#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main() {
    vector<int> data(65536);
    ifstream file("data.txt");
    
    for (int i = 0; i < 65536; i++) {
        file >> data[i];
    }
    file.close();
    
    bubbleSort(data);
    
    ofstream out("bubble_sorted.txt");
    for (int x : data) {
        out << x << "\n";
    }
    out.close();
    
    return 0;
}