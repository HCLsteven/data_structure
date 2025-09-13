#include <iostream>
#include <cstring>   // strlen
using namespace std;

int main() {
    int n;
    cout << "請輸入學生人數: ";
    cin >> n;
    cin.ignore();  // 忽略掉 cin >> 留下的 '\n'

    // 先輸入所有姓名，並同時計算最長長度
    char** names = new char*[n];
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        char buffer[200];   // 暫存輸入，假設名字不會超過 200
        cout << "請輸入學生姓名 #" << i + 1 << ": ";
        cin.getline(buffer, 200);

        int len = strlen(buffer);
        if (len > maxLen) {
            maxLen = len;  // 更新最長長度
        }

        names[i] = new char[len + 1]; // 剛好配置足夠空間
        strcpy(names[i], buffer);
    }

    // 輸出置中對齊結果
    cout << "\n對齊後輸出:\n";
    for (int i = 0; i < n; i++) {
        int len = strlen(names[i]);
        int leftPadding = (maxLen - len) / 2;
        int rightPadding = maxLen - len - leftPadding;

        // 輸出左邊空格
        for (int j = 0; j < leftPadding; j++) cout << " ";
        cout << names[i];
        // 輸出右邊空格
        for (int j = 0; j < rightPadding; j++) cout << " ";
        cout << endl;
    }

    // 釋放記憶體
    for (int i = 0; i < n; i++) {
        delete[] names[i];
    }
    delete[] names;

    return 0;
}
