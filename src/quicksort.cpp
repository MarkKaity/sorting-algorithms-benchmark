#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>

// Phân hoạch Hoare với Pivot ở giữa
int partition(std::vector<double>& arr, int low, int high) {
    double pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) return j;

        std::swap(arr[i], arr[j]);
    }
}

void quickSort(std::vector<double>& arr, int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) return 0;

    std::vector<double> arr(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // 1. Bấm giờ bắt đầu
    clock_t start = clock();

    // 2. Chạy Quick Sort
    if (n > 0) {
        quickSort(arr, 0, n - 1);
    }

    // 3. Bấm giờ kết thúc
    clock_t end = clock();

    double time_in_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double time_in_ms = time_in_sec * 1000.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "So luong phan tu: " << n << "\n";
    std::cout << "Thoi gian sap xep (Quick Sort): " << time_in_ms << " ms (" << time_in_sec << " s)\n";

    return 0;
}