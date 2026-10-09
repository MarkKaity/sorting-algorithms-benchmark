#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm> // Thư viện chứa std::sort

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

    // 2. Chạy std::sort của C++
    std::sort(arr.begin(), arr.end());

    // 3. Bấm giờ kết thúc
    clock_t end = clock();

    double time_in_sec = (double)(end - start) / CLOCKS_PER_SEC;
    double time_in_ms = time_in_sec * 1000.0;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "So luong phan tu: " << n << "\n";
    std::cout << "Thoi gian sap xep (std::sort): " << time_in_ms << " ms (" << time_in_sec << " s)\n";

    return 0;
}