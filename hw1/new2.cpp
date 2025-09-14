#include <iostream>
#include <cstring>  // strlen, strchr, strncpy
using namespace std;

int main() {
    int n;
    cout << "請輸入學生人數: ";
    cin >> n;
    cin.ignore();

    // 使用一維陣列儲存指標
    char* names[100];  // 最多 100 人
    int maxFirstLen = 0;

    for (int i = 0; i < n; i++) {
        char buffer[200];
        cout << "請輸入學生姓名 #" << i + 1 << ": ";
        cin.getline(buffer, 200);

        // 配置記憶體存放姓名
        names[i] = new char[strlen(buffer) + 1];
        strcpy(names[i], buffer);

        // 找到空格 → 分隔名字與姓氏
        char* space = strchr(names[i], ' ');
        int firstLen = 0;
        if (space != nullptr) {
            firstLen = space - names[i];  // 計算左邊長度
        } else {
            firstLen = strlen(names[i]);  // 沒有姓氏時，整個字串算左邊
        }

        if (firstLen > maxFirstLen) {
            maxFirstLen = firstLen;
        }
    }

    // 輸出結果，左邊補空格
    cout << "\n對齊後輸出:\n";
    for (int i = 0; i < n; i++) {
        char* space = strchr(names[i], ' ');
        int firstLen = 0;
        if (space != nullptr) {
            firstLen = space - names[i];
        } else {
            firstLen = strlen(names[i]);
        }

        int padding = maxFirstLen - firstLen;

        // 輸出左邊部分
        for (int j = 0; j < padding; j++) cout << " ";
        cout << names[i] << endl;
    }

    // 釋放記憶體
    for (int i = 0; i < n; i++) {
        delete[] names[i];
    }

    return 0;
}
