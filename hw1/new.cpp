#include <iostream>
#include <cstring>  // strlen
using namespace std;

int main() {
    int n, m;
    cout << "請輸入學生人數和最大姓名長度: ";
    cin >> n >> m;
    cin.ignore();  // 忽略 cin >> 後的換行符

    // 使用 new 建立動態二維陣列
    char** names = new char*[n];
    for (int i = 0; i < n; i++) {
        names[i] = new char[m + 1];  // +1 for '\0'
        cout << "輸入姓名 #" << i + 1 << ": ";
        cin.getline(names[i], m + 1);  // 可讀入空格
    }

    // 建立指標陣列，進行排序時交換指標
    char** ptr_array = new char*[n];
    for (int i = 0; i < n; i++) {
        ptr_array[i] = names[i];
    }

    // Bubble Sort 根據最後一個字元 ASCII 值排序
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int len1 = strlen(ptr_array[j]);
            int len2 = strlen(ptr_array[j + 1]);
            char last1 = ptr_array[j][len1 - 1];
            char last2 = ptr_array[j + 1][len2 - 1];

            if (last1 > last2) {
                char* temp = ptr_array[j];
                ptr_array[j] = ptr_array[j + 1];
                ptr_array[j + 1] = temp;
            }
        }
    }

    // 輸出排序後結果
    cout << "\n排列後:\n";
    for (int i = 0; i < n; i++) {
        cout << ptr_array[i] << endl;
    }

    // 釋放記憶體
    for (int i = 0; i < n; i++) {
        delete[] names[i];
    }
    delete[] names;
    delete[] ptr_array;

    return 0;
}
