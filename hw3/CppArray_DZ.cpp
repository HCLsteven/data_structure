#include <iostream>
#include <stdexcept>
using namespace std;
 
class CppArray{
    private:
    int defaultSize;
    float* value;
    public:
    
    CppArray (int s = 5) {
        defaultSize = s;
        value = new float[defaultSize];
        for (int i = 0; i < defaultSize; i++)
            value[i] = 0;
    }

    CppArray& operator=(CppArray& tmp) {
    delete[] value;
    defaultSize = tmp.defaultSize;
    value = new float[defaultSize];

    for (int i = 0; i < defaultSize; i++)
        value[i] = tmp.value[i];
    return tmp;
    }

    friend istream& operator>>(istream& in, CppArray& arr) {
        for (int i = 0; i < arr.defaultSize; i++) {
            cin >> arr.value[i];
        }
    }

    friend ostream& operator<<(ostream& out, const CppArray& arr) {
        cout << "{ ";
        for (int i = 0; i < arr.defaultSize; i++) {
            cout << arr.value[i];
            if (i != arr.defaultSize - 1)
                cout << ", ";
        }
        cout << " }";
    }

    float& operator[](int p) {
        if (p < 0 || p >= defaultSize)
            throw out_of_range("超出範圍");
    }

    int getsize() {
        return defaultSize;
    }

    ~CppArray() {
        delete[] value;
    }
};
int main() {
    CppArray arr(4);
    cin >> arr;
    cout << arr << endl;
    CppArray arr2(2);
    cout << arr.getsize() << endl;
    arr2 = arr;
    cout << arr2 << endl;
    cout << arr[5] << endl;
    return 0;
}
