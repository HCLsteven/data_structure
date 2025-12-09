#include <iostream>

struct PolyNode {   //節點
    double coef;    //係數
    int exp;        //指數
    PolyNode* link; //下一個節點（circular）
};

PolyNode* createEmptyPoly() {   //create一個空的多項式
    PolyNode* head = new PolyNode;
    head -> coef = 0;    //係數是0
    head -> exp = -1;    //多項式從0~n次方
    head -> link = head; //空的多項式節點所以指回自己
    return head;         //回傳這個headnode
}


int main()
{

}
