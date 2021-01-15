#include<string>
#include<vector>
#include<iostream>
using namespace std;

int dp_memo(string word1, int i, string word2, int j, vector<vector<int>>& memo)
{
	// 如果i 或j 任一个比较完所有字符，则f(i, j) = i + j
    if(i == 0 || j == 0){
        return i + j;
    }
    // 如果f(i, j) 的值已经保存在备忘录中，则直接返回f(i, j) = memo[i][j]
    if(memo[i][j] != INT_MAX)
        return memo[i][j];
    else{
   		// 如果word1[i - 1]与word2[j - 1]字符相等，则f(i, j) = f(i-1,j-1)
        if(word1[i - 1] == word2[j - 1]){
            memo[i][j] = dp_memo(word1, i - 1, word2, j - 1, memo);
            return memo[i][j];
        } else {
        	// 如果word1[i - 1]与word2[j - 1]字符不相等，则f(i, j) = min{f(i-1,j-1),f(i,j-1),f(i-1,j)} + 1
            int rep = dp_memo(word1, i - 1, word2, j - 1, memo) + 1;
            int ins = dp_memo(word1, i, word2, j - 1, memo) + 1;
            int del = dp_memo(word1, i - 1, word2, j, memo) + 1;
            memo[i][j] = min(rep, min(ins, del));
            return memo[i][j];
        }
    }
}

int dp_iter(string word1, string word2)
{
    int len1 = word1.length();
    int len2 = word2.length();
    // 创建状态转移表
    int dp[len1 + 1][len2 + 1];
    // 初始化状态转移表，也即其中一个字符串为空时的情况
    for(int i = 0; i <= len1; ++i)
        dp[i][0] = i;
    for(int j = 0; j <= len2; ++j)
        dp[0][j] = j;
    // 按照状态转移方程从初始状态往后依次填表
    for(int i = 1; i <= len1; ++i){
        for(int j = 1; j <= len2; ++j){
            if(word1[i-1] == word2[j-1]){
                dp[i][j] = dp[i - 1][j - 1];
            }else{
                int ins = dp[i][j - 1] + 1;
                int del = dp[i - 1][j] + 1;
                int rep = dp[i - 1][j - 1] + 1;
                dp[i][j] = min(rep, min(ins, del));
            }
        }
    }
    return dp[len1][len2];
}

int main(void)
{
    int method;
    
    printf("leetcode-72 dp_memo solution    : 1\n");
    printf("leetcode-72 dp_iter solution    : 2\n");
    printf("Select  algorithm: ");
    scanf("%d", &method);

    string word1 = "mitcmu";
    string word2 = "mtacnu";
    int len1 = word1.length();
    int len2 = word2.length();
    vector<vector<int>> memo;
    int eDist = 0;

    switch (method)
    {
    case 1:
        memo.resize(len1 + 1, vector<int>(len2 + 1, INT_MAX));
        dp_memo(word1, len1, word2, len2, memo);
        eDist = memo[len1][len2];
        break;

    case 2:
        eDist = dp_iter(word1, word2);
        break;
    
    default:
        break;
    }

    cout << "Edit Distance:" << eDist << endl;

    return 0;
}