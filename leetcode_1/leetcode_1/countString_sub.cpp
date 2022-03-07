#include<iostream>

using namespace std;

/***
* 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
* 
示例 1:
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。

示例 4:
输入: s = ""
输出: 0

提示：
0 <= s.length <= 5 * 104
s 由英文字母、数字、符号和空格组成

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-substring-without-repeating-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
***/

int MAX = 0;
int strlen(const string& s) {
    int count = 0;
    while (s[count++] != '\0');
    return count - 1;
}

bool isNotInstr(const string& s,char c){
    if (s == "")
        return true;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == c)
            return false;
    }
    return true;
}

int lengthOfLongestSubstring(string s) {
    if (s == "")
        return 0;
    if (strlen(s) == 1)
        return 1;
    string str="";
    int lenS = 0;
    for (int j = 0; j < strlen(s); j++) {
        for (int i = j; i < strlen(s); i++) {
            char c = s[i];
            if (isNotInstr(str, c)) {
                str += c;
                lenS++;
            }
            else {
                MAX = lenS > MAX ? lenS : MAX;
                lenS = 0;
                str = "";
                break;
            }
        }
        MAX = lenS > MAX ? lenS : MAX;
    }
    
    return MAX;
}