#include<iostream>
#include"listNodeAdd.h"

using namespace std;
/***
* 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
示例 2：

输入：l1 = [0], l2 = [0]
输出：[0]
示例 3：

输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]

注意：
每个链表中的节点数在范围 [1, 100] 内
0 <= Node.val <= 9
题目数据保证列表表示的数字不含前导零

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/add-two-numbers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
***/

int length(ListNode* L) {//计算包含头结点
    int count = 0;
    while (L) {
        count++;
        L = L->next;
    }
    return count;
}
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {//按题目，带头结点
    ListNode* result = new ListNode;
    ListNode* tmpL = result;
    int out = 0, lth = 0, lth1 = length(l1), lth2 = length(l2);
    while (l1 || l2) {
        int val1 = 0,val2=0;
        if (l1)
            val1 = l1->val;
        if (l2)
            val2 = l2->val;
        int vtmp = val1 + val2 + out;
        if (vtmp <= 9) {
            out = 0;
        }
        else {
            vtmp = vtmp % 10;
            out = 1;
        }
        ListNode* tmpNode = new ListNode;
        tmpNode->val = vtmp;
        tmpL->next = tmpNode;
        tmpL = tmpNode;
        lth++;
        if(l1)
            l1 = l1->next;
        if(l2)
        l2 = l2->next;
    }
    if (out) {
        ListNode* tmpNode = new ListNode;
        tmpNode->val = out;
        tmpL->next = tmpNode;
    }
    tmpL = result;
    result = result->next;
    delete tmpL;
    //cout << "lth:" << lth << endl;
    return result;//由于result是新创建的表，创建时带了头结点，完成操作后需要删除头结点
}

ListNode* creatList() {//带头结点建立
    ListNode* L = new ListNode;
    ListNode* p = L;
    int x;
    cin >> x;
    while (x != -1) {
        ListNode* tmp = new ListNode;
        tmp->val = x;
        p->next = tmp;
        p = tmp;
        cin >> x;
    }
    p = L;
    L = L->next;
    delete p;
    return L;//返回时去掉头结点，以后各函数中的表头结点就直接可以参与运算
}

void showL(ListNode* L) {//会输出头结点
    int count = 1;
    cout << "[";
    while (L) {
        if (count == 1) {
            cout << L->val;
        }
        else {
            cout << ',' << L->val ;
        }
        count++;
        L = L->next;
    }
    cout << "]"<<endl;
}

