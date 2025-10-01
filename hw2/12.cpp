#include <iostream>
#include <ctime>    // clock()
#include <cstdlib>  // rand(), srand()
using namespace std;

// 選擇排序
void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // 交換
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

int main() {
    srand(time(0)); // 產生隨機數種子

    // 測試不同大小的 n
    for (int n = 500; n <= 3000; n += 500) {
        int* arr = new int[n];

        // 產生 worst-case (降序排列)
        for (int i = 0; i < n; i++) {
            arr[i] = n - i;
        }

        clock_t start = clock();
        selectionSort(arr, n);
        clock_t end = clock();

        double duration = double(end - start) / CLOCKS_PER_SEC;

        cout << "n = " << n << " , time = " << duration << " sec" << endl;

        delete[] arr; // 釋放動態記憶體
    }

    return 0;
}
