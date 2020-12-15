#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

int main(int argc, char* argv[])
{
    const string delim(" \t,.;");      // 单词分隔符
    string line;                       // 存储每行字符串
    cout << "Please   input: ";
    // 循环读取每行字符串
    while (getline(cin, line))
    {
        // 先反转每行所有字符
        reverse(line.begin(), line.end());

        string::size_type begIdx, endIdx;
        begIdx = line.find_first_not_of(delim);             // 查找第一个单词的首字符索引
        cout << "Reverse output: ";
        while (begIdx != string::npos)
        {
            endIdx = line.find_first_of(delim, begIdx);     // 查找一个单词末字符的后一位索引
            if(endIdx == string::npos)
                endIdx = line.length();                     // 一行的最后一个单词特殊处理

            // 反向打印单词，因之前将字符串反转了，将单词顺序纠正过来
            for(int i = endIdx - 1; i >= static_cast<int>(begIdx); i--)
                cout << line[i];
            cout << ' ';

            begIdx = line.find_first_not_of(delim, endIdx); // 查找下一个单词的首字符索引
        }
        cout << endl << endl;
        cout << "Please   input: ";
    }
    return 0;
}