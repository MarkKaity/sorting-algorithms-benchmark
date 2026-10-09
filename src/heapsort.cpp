#include <iostream>
#include <vector>
#include <ctime>      // Thư viện chuẩn đo thời gian đơn giản
#include <iomanip>

// Các hàm heapify và heapSort giữ nguyên
void heapify(std::vector<double>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<double>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
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

    // 2. Chạy thuật toán
    heapSort(arr);

    // 3. Bấm giờ kết thúc
    clock_t end = clock();

    // 4. Tính thời gian (chia cho CLOCKS_PER_SEC để ra giây)
    double time_in_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double time_in_ms = time_in_sec * 1000.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "So luong phan tu: " << n << "\n";
    std::cout << "Thoi gian sap xep: " << time_in_ms << " ms (" << time_in_sec << " s)\n";

    return 0;
}