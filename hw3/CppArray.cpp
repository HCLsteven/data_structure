#include <iostream>
#include <stdexcept>  // std::out_of_range
#include <iomanip>    // (可選) 讓輸出更漂亮
using namespace std;

class CppArray {
public:
    // 預設參數：大小與初值（可依需求調整）
    explicit CppArray(int size = 10, float initValue = 0.0f)
        : _n(size), _a(nullptr)
    {
        if (_n < 0) throw invalid_argument("size must be non-negative");
        _a = (_n > 0) ? new float[_n] : nullptr;
        for (int i = 0; i < _n; ++i) _a[i] = initValue;
    }

    // 複製建構子（深拷貝）
    CppArray(const CppArray& other)
        : _n(other._n), _a(nullptr)
    {
        _a = (_n > 0) ? new float[_n] : nullptr;
        for (int i = 0; i < _n; ++i) _a[i] = other._a[i];
    }

    // 指派運算子（深拷貝 + 自我指派保護）
    CppArray& operator=(const CppArray& other) {
        if (this == &other) return *this;     // 自我指派
        // 先配置新空間，再釋放舊空間（strong exception safety）
        float* newArr = (other._n > 0) ? new float[other._n] : nullptr;
        for (int i = 0; i < other._n; ++i) newArr[i] = other._a[i];
        delete[] _a;
        _a = newArr;
        _n = other._n;
        return *this;
    }

    // 解構子
    ~CppArray() { delete[] _a; }

    // 下標運算子（含範圍檢查）—— 非 const 版本
    float& operator[](int i) {
        rangeCheck(i);
        return _a[i];
    }

    // 下標運算子（含範圍檢查）—— const 版本，供常量物件使用
    const float& operator[](int i) const {
        rangeCheck(i);
        return _a[i];
    }

    // 取得大小
    int GetSize() const { return _n; }

    // 友元：輸出運算子（cout << a）
    friend ostream& operator<<(ostream& os, const CppArray& arr) {
        os << "[";
        for (int i = 0; i < arr._n; ++i) {
            if (i) os << ' ';
            os << arr._a[i];
        }
        os << "]";
        return os;
    }

    // 友元：輸入運算子（cin >> a）
    // 依序讀入 arr._n 個數值
    friend istream& operator>>(istream& is, CppArray& arr) {
        for (int i = 0; i < arr._n; ++i) {
            is >> arr._a[i];
        }
        return is;
    }

private:
    int    _n;   // 陣列大小
    float* _a;   // 動態配置陣列

    void rangeCheck(int i) const {
        if (i < 0 || i >= _n)
            throw out_of_range("CppArray index out of range");
    }
};

/* ------------------ 測試範例 ------------------ */
int main() {
    // (a) 建構：大小 5、初值 1.5
    CppArray a(5, 1.5f);
    cout << "a = " << a << "\n";  // [1.5 1.5 1.5 1.5 1.5]

    // (e) 下標存取與範圍檢查
    a[2] = 3.14f;
    cout << "a[2] = " << a[2] << "\n";     // 3.14
    cout << "a = " << a << "\n";           // [1.5 1.5 3.14 1.5 1.5]

    // (b) 複製建構子（深拷貝）
    CppArray b = a;         // copy constructor
    b[0] = 9.9f;
    cout << "b = " << b << "\n";           // [9.9 1.5 3.14 1.5 1.5]
    cout << "a = " << a << "\n";           // a 不受影響

    // (c) 指派運算子（深拷貝）
    CppArray c(3, 0.0f);
    c = a;                                  // operator=
    cout << "c = " << c << "\n";

    // (f) 取得大小
    cout << "size of c : " << c.GetSize() << "\n";

    // (g) 輸入運算子
    cout << "請輸入 " << c.GetSize() << " 個浮點數：";
    cin >> c;                               // 例如輸入：1 2 3 4 5
    cout << "c = " << c << "\n";

    // (i) 範圍檢查示範：解註解可測試例外
    // cout << a[99] << endl;  // 會丟出 out_of_range

    return 0;
}
