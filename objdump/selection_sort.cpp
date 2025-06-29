#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[min_idx], arr[i]);
    }
}

int main() {
    vector<int> data(65536);
    ifstream file("data.txt");
    
    for (int i = 0; i < 65536; i++) {
        file >> data[i];
    }
    file.close();
    
    selectionSort(data);
    
    ofstream out("selection_sorted.txt");
    for (int x : data) {
        out << x << "\n";
    }
    out.close();
    
    return 0;
}