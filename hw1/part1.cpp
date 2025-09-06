#include <iostream>
#include <string>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of students and max name length: ";
    cin >> n >> m;
    cin.ignore(); // 忽略 cin >> 後的 '\n'

    // 建立二維動態陣列
    char** names = (char**)malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        names[i] = (char*)malloc((m + 1) * sizeof(char)); // 配置空間
        cout << "Enter name #" << i + 1 << ": ";
        cin.getline(names[i], m + 1); // 讀取完整一行（含空格）
    }

    // 顯示學生姓名
    cout << "\nStudent names:\n";
    for (int i = 0; i < n; i++) {
        cout << names[i] << endl;
    }

    // 釋放記憶體
    for (int i = 0; i < n; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}
