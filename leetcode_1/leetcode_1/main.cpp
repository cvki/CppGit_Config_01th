#include<iostream>
#include<string>
#include"listNodeAdd.h"

using namespace std;

//第一题
ListNode* creatList();
void showL(ListNode* L);
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

//第二题
int lengthOfLongestSubstring(string s);

int main() {
#if 0
    ListNode* l1 = creatList();
    ListNode* l2 = creatList();
    showL(l1);
    showL(l2);
    //cout << "L1长度：" << length(l1) << "\t" << "L2长度：" << length(l2) << endl;
    ListNode* l = addTwoNumbers(l1, l2);
    showL(l);
#endif
    string s;
    cin >> s;
    cout << lengthOfLongestSubstring(s) << endl;
    return 0;
}