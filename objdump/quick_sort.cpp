#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    vector<int> data(65536);
    ifstream file("data.txt");
    
    for (int i = 0; i < 65536; i++) {
        file >> data[i];
    }
    file.close();
    
    quickSort(data, 0, 65535);
    
    ofstream out("quick_sorted.txt");
    for (int x : data) {
        out << x << "\n";
    }
    out.close();
    
    return 0;
}