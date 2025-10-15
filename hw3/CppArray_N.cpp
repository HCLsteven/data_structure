#include <iostream>
#include <stdexcept>
using namespace std;

class CppArray {
private:
    int   defaultSize;
    float* value;

public:
    // 建構子
    CppArray(int s = 5){
        defaultSize = s;
        value = nullptr;
        if (defaultSize < 0) throw invalid_argument("size must be non-negative");
        value = (defaultSize > 0) ? new float[defaultSize] : nullptr;
        for (int i = 0; i < defaultSize; ++i) value[i] = 0.0f;
    }

    // 複製建構子（深拷貝）
    CppArray(const CppArray& other){
        defaultSize = other.defaultSize;
        value = nullptr; 
        value = (defaultSize > 0) ? new float[defaultSize] : nullptr;
        for (int i = 0; i < defaultSize; ++i) value[i] = other.value[i];
    }

    // 指派運算子（深拷貝 + 自我指派保護）
    CppArray& operator=(const CppArray& tmp) {
        if (this == &tmp) return *this; // 自我指派
        float* newBuf = (tmp.defaultSize > 0) ? new float[tmp.defaultSize] : nullptr;
        for (int i = 0; i < tmp.defaultSize; ++i) newBuf[i] = tmp.value[i];
        delete[] value;
        value = newBuf;
        defaultSize = tmp.defaultSize;
        return *this;
    }

    // 輸入運算子
    friend istream& operator>>(istream& in, CppArray& arr) {
        for (int i = 0; i < arr.defaultSize; ++i) {
            in >> arr.value[i];
        }
        return in;
    }

    // 輸出運算子
    friend ostream& operator<<(ostream& out, const CppArray& arr) {
        out << "{ ";
        for (int i = 0; i < arr.defaultSize; ++i) {
            out << arr.value[i];
            if (i != arr.defaultSize - 1) out << ", ";
        }
        out << " }";
        return out;
    }

    // 下標運算子（含範圍檢查）
    float& operator[](int p) {
        if (p < 0 || p >= defaultSize) throw out_of_range("超出範圍");
        return value[p];
    }
    const float& operator[](int p) const {
        if (p < 0 || p >= defaultSize) throw out_of_range("超出範圍");
        return value[p];
    }

    int getsize() const {
        return defaultSize;
    }

    ~CppArray() {
        delete[] value;
    }
};

int main() {
    int size;
    cout << "請輸入陣列大小: ";
    cin >> size;

    // 使用使用者輸入的大小建立物件
    CppArray arr(size);

    cout << "請輸入 " << arr.getsize() << " 個浮點數: ";
    cin >> arr;
    cout << "輸入的陣列為: " << arr << endl;

    CppArray arr2(2);
    cout << "arr 的大小為: " << arr.getsize() << endl;

    arr2 = arr;
    cout << "arr2 = arr 複製後: " << arr2 << endl;

    try {
        cout << arr[5] << endl;  // 可能超出範圍
    } catch (const out_of_range& e) {
        cerr << "例外捕獲: " << e.what() << endl;
    }

    return 0;
}
