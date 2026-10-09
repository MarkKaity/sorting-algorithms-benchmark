#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

// Trộn 2 nửa mảng con
void merge(std::vector<double>& arr, std::vector<double>& temp, int left, int mid, int right) {
    int i = left;      // Con trỏ nửa trái
    int j = mid + 1;   // Con trỏ nửa phải
    int k = left;      // Con trỏ mảng tạm

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (int p = left; p <= right; ++p) {
        arr[p] = temp[p];
    }
}

void mergeSort(std::vector<double>& arr, std::vector<double>& temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, temp, left, mid);
        mergeSort(arr, temp, mid + 1, right);
        merge(arr, temp, left, mid, right);
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

    // Mảng tạm hỗ trợ merge
    std::vector<double> temp(n);

    // 1. Bấm giờ bắt đầu
    clock_t start = clock();

    // 2. Chạy Merge Sort
    if (n > 0) {
        mergeSort(arr, temp, 0, n - 1);
    }

    // 3. Bấm giờ kết thúc
    clock_t end = clock();

    double time_in_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double time_in_ms = time_in_sec * 1000.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "So luong phan tu: " << n << "\n";
    std::cout << "Thoi gian sap xep (Merge Sort): " << time_in_ms << " ms (" << time_in_sec << " s)\n";

    return 0;
}