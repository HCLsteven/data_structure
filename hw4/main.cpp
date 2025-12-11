#include <iostream>
#include <ctime>
#include <cstdlib> // rand(), srand()
using namespace std;

struct PolyNode {   //節點
    double coef;    //係數
    int exp;        //指數
    PolyNode* link; //下一個節點（circular）
};

PolyNode* createEmptyPoly() {   //create一個空的多項式
    PolyNode* head = new PolyNode; //head 是一個指標，指向一個 PolyNode 物件
    head -> coef = 0;    //係數是0
    head -> exp = -1;    //head 不是實際的多項式項 多項式0~n次方
    head -> link = head; //空的多項式節點所以指回自己
    return head;         //回傳這個headnode
}   

void insertTerm(PolyNode* head, double coef, int exp) {     //insert時需要head指標 係數 指數
    if (coef == 0.0) return;                //如果係數是0就不用插入了
    PolyNode* prev = head;                  //將head設為previous
    PolyNode* curr = head->link;            //將head指向的下一個設為current 
    while (curr != head && curr->exp > exp) {   //當current不是head 且 current指向的指數大於正要插入的指數  
        prev = curr;                        //將previous跳到下一個變成current
        curr = curr->link;                  //而current變成原本current的下一個
    }
    if (curr != head && curr->exp == exp) { //如果current不是head 且 current指向的指數等於正要插入的指數
        curr->coef += coef;                 //current指向的係數和正要插入的係數相加
        if (curr->coef == 0.0) {            //如果current的係數等於0        
            prev->link = curr->link;        //讓上一個的link指向下一個
            delete curr;                    //把現在這個係數等於0的刪掉
        }
    } else {                                //如果沒有這個指數
        PolyNode* node = new PolyNode;      //新增一個node插入
        node->coef = coef;                  //讓他指向的係數等於要插入的係數
        node->exp  = exp;                   //指數等於要插入的指數
        node->link = curr;                  //讓node的link指向current
        prev->link = node;                  //讓previous的link指向node
    }
}

PolyNode* readPoly() {                      //讀入一個多項式
    int terms;                              //項數
    cout << "請輸入多項式的項數: ";         
    cin >> terms;                           //輸入項數

    PolyNode* head = createEmptyPoly();     //先建立一個空的多項式

    cout << "請依序輸入每一項的「係數 指數」(例如: 5 2 表示 5x^2)\n";
    for (int i = 0; i < terms; i++) {       //當i<terms時 (例如terms=2 i=0 1 執行兩次)
        double c;                           //係數
        int e;                              //指數
        cout << "第 " << i + 1 << " 項 (係數 指數): ";
        cin >> c >> e;                      //輸入係數 指數
        insertTerm(head, c, e);             //insertTerm 插入空的多項式
    }

    return head;                            //回傳這個多項式的 head指標
}


void printPoly(PolyNode* head) {    //print出多項式
    PolyNode* p = head->link;       //node指標p指向第一項
    bool first = true;              // 宣告布林變數並賦值true(1)
    while (p != head) {             //當p不是指向head時
        if (!first) cout << " + ";  //如果不是第一個就輸出 +
        cout << p->coef << "x^" << p->exp;  //輸出 p指向的係數 "x^" p指向的指數
        first = false;              //不是第一個了 first變false(0)
        p = p->link;                //指向下一個
    }
    cout << endl;                   //跳出while loop後換行
}

PolyNode* polyMultiply(PolyNode* aHead, PolyNode* bHead) {  //乘法 傳進來的是a/b的head的node指標
    PolyNode* cHead = createEmptyPoly();                    //create一個空的多項式cHead (c)
    for (PolyNode* pa = aHead->link; pa != aHead; pa = pa->link) {      //宣告一個指標pa指向a的第一個實際節點
        for (PolyNode* pb = bHead->link; pb != bHead; pb = pb->link) {  //當指標不指向head時繼續 ; 指向至下一個
            double c = pa->coef * pb->coef;                 //係數相乘
            int    e = pa->exp + pb->exp;                   //指數相加
            insertTerm(cHead, c, e);                        //插入c多項式
        }
    }
    return cHead;                                           //回傳c的head指標
}

void deletePoly(PolyNode* head) {   //釋放記憶體
    PolyNode* p = head->link;       //p指向第一項
    while (p != head) {             //當p不是指向head時
        PolyNode* tmp = p;          //因為p等一下要指向下一個節點 需要一個tmp來指向目前要刪掉的節點
        p = p->link;                //p指向下一個節點
        delete tmp;                 //刪掉tmp指向的節點
    }
    delete head;                    
}

PolyNode* dense(int n){             //生成dense多項式
    PolyNode* head = createEmptyPoly();
    for(int i = 0; i < n; i++){
        insertTerm(head, 1.0, i);   //插入dense多項式
    }
    return head;
}

PolyNode* nondense(int n){          //生成nondense多項式
    PolyNode* head = createEmptyPoly();
    for(int i = 0; i < n; i++){
        int exp = rand() % 100000;  //隨機生成指數
        insertTerm(head, 1.0, exp); //插入nondense多項式
    }
    return head;
}


int main() {
    cout << "輸入多項式 a:\n";
    PolyNode* a = readPoly();       //呼叫讀入多項式

    cout << "輸入多項式 b:\n";
    PolyNode* b = readPoly();

    cout << "a = "; printPoly(a);   //print出讀入的多項式
    cout << "b = "; printPoly(b);

    PolyNode* c = polyMultiply(a, b);   //乘法

    cout << "c = a * b = ";
    printPoly(c);

    deletePoly(a);  //釋放記憶體
    deletePoly(b);
    deletePoly(c);
    //實驗=================================================================
    srand(time(0));    // 讓 nondense() 變成真正的亂數

    int nList[] = {10, 100, 1000, 2000};  // b 
    int N = sizeof(nList) / sizeof(nList[0]);   //三個所以做三次

    const int TRIALS = 3;  // 每組做 3 次取平均

    cout << "n,dense_ms,nondense_ms\n";

    for(int i=0;i<N;i++){
        int n = nList[i];

        // ===== dense =====
        PolyNode* a = dense(100);   // a 固定 100 項
        PolyNode* b = dense(n);     // b = n 項
        double totalDense = 0.0;    //設定dense總花費時間
        for(int t=0;t<TRIALS;t++){  //每組做 3 次取平均
            clock_t start = clock();
            PolyNode* c = polyMultiply(a,b); //ab相乘
            clock_t end = clock();
            totalDense += double(end - start) / CLOCKS_PER_SEC;     //所有 TRIALS次的總秒數 = 這次的秒數 + 之前加起來的
            deletePoly(c);
        }
        deletePoly(a);
        deletePoly(b);
        double avgDenseMs = (totalDense / TRIALS) * 1000.0;     //dense一次乘法的平均秒數

        // ===== nondense =====
        a = nondense(100);
        b = nondense(n);
        double totalNondense = 0.0; //設定nondense總花費時間
        for(int t=0;t<TRIALS;t++){
            clock_t start = clock();
            PolyNode* c = polyMultiply(a,b);
            clock_t end = clock();
            totalNondense += double(end - start) / CLOCKS_PER_SEC;
            deletePoly(c);
        }

        deletePoly(a);
        deletePoly(b);

        double avgNondenseMs = (totalNondense / TRIALS) * 1000.0; //nondense一次乘法的平均秒數

        // ===== 輸出實驗結果 =====
        cout << n << "," << avgDenseMs << "," << avgNondenseMs << "\n";
    }
    return 0;
}
