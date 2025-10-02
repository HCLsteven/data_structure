#include <iostream>
#include <cstdlib>   // rand, srand
#include <ctime>     // time, clock, CLOCKS_PER_SEC
using namespace std;

int BinarySearch(const int a[], int n, int x) {
    int L = 0, R = n - 1;
    while (L <= R) {
        // 用無溢位的寫法也行：int mid = L + (R - L) / 2;
        int mid = (L + R) / 2;
        if (x < a[mid]) R = mid - 1;
        else if (x > a[mid]) L = mid + 1;
        else return mid;
    }
    return -1;
}

// 防止編譯器把計算結果丟掉
static volatile int sink;

int main() {
    srand((unsigned)time(0));
    cout << "n, avg_time_per_search_ns\n";

    for (int n = 10; n <= 100; n += 10) {
        int* arr = new int[n];
        for (int i = 0; i < n; ++i) arr[i] = i + 1;

        const int TRIALS = 30;       // 做多次取平均，降低抖動
        const int RUNS   = 200000;   // 每次 trial 連做很多次搜尋

        double total_seconds = 0.0;

        for (int t = 0; t < TRIALS; ++t) {
            int sum = 0;
            clock_t start = clock();
            for (int r = 0; r < RUNS; ++r) {
                int target = rand() % (n * 2);  // 有時存在、有時不存在
                sum += BinarySearch(arr, n, target) + 1; // 改變 sum，避免被消掉
            }
            clock_t end = clock();
            total_seconds += double(end - start) / CLOCKS_PER_SEC;
            sink = sum;  // 使用結果，防止最佳化
        }

        double avg_ns = total_seconds * 1e9 / (TRIALS * RUNS);
        cout << n << ", " << avg_ns << '\n';

        delete[] arr;
    }
    return 0;
}
