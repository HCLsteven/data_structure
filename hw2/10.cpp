#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time, clock

using namespace std;

// BinarySearch 函數 (使用陣列)
int BinarySearch(int arr[], int n, int x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (x < arr[mid]) {
            right = mid - 1;
        } else if (x > arr[mid]) {
            left = mid + 1;
        } else {
            return mid; // 找到
        }
    }
    return -1; // 沒找到
}

int main() {
    srand(time(0));  // 設定亂數種子

    cout << "n, average_time(clock ticks)" << endl;

    // 測試 n 從 10 到 100，每次增加 10
    for (int n = 10; n <= 100; n += 10) {
        int* arr = new int[n]; // 動態配置陣列
        for (int i = 0; i < n; i++) {
            arr[i] = i + 1; // 已排序好的陣列 [1,2,...,n]
        }

        int trials = 1000;   // 每個 n 測試 1000 次
        double total_time = 0;

        for (int t = 0; t < trials; t++) {
            int target = rand() % (n * 2); // 可能存在，也可能不存在

            clock_t start = clock();
            BinarySearch(arr, n, target);
            clock_t end = clock();

            total_time += (double)(end - start);
        }

        double avg_time = total_time / trials;
        cout << n << ", " << avg_time << endl;

        delete[] arr; // 釋放記憶體
    }

    return 0;
}
