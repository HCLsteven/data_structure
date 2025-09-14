#include <iostream>
#include <cstring>   // strlen, strchr, strcpy
#include <cstdlib>   // malloc, free
using namespace std;

int main() {
    int n;
    cout << "請輸入學生人數: ";
    cin >> n;
    cin.ignore();  // 忽略掉 cin >> 留下的 '\n'

    // 使用 malloc 配置一維指標陣列
    char** names = (char**)malloc(n * sizeof(char*));
    int maxFirstLen = 0;

    for (int i = 0; i < n; i++) {
        char buffer[200];   // 暫存輸入
        cout << "請輸入學生姓名 #" << i + 1 << ": ";
        cin.getline(buffer, 200);

        // 配置剛好需要的記憶體
        names[i] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(names[i], buffer);

        // 找到空格 → 分隔名字與姓氏
        char* space = strchr(names[i], ' ');
        int firstLen = 0;
        if (space != nullptr) {
            firstLen = space - names[i];
        } else {
            firstLen = strlen(names[i]);
        }

        if (firstLen > maxFirstLen) {
            maxFirstLen = firstLen;
        }
    }

    // 輸出結果：根據左邊最長長度補空格
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

        for (int j = 0; j < padding; j++) cout << " ";
        cout << names[i] << endl;
    }

    // 釋放記憶體
    for (int i = 0; i < n; i++) {
        free(names[i]);
    }
    free(names);

    return 0;
}
