#include<vector>
#include<string>
#include<iostream>
using namespace std;

bool isValid(vector<string>& board, int row, int col)
{
    // 任何两个皇后都不能处于同一列
    for (int i = 0; i < row; i++){
        if(board[i][col] == 'Q')
            return false;
    }
    // 任何两个皇后都不能处于同一左上右下对角线
    for(int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--){
        if(board[i][j] == 'Q')
            return false;
    }
    // 任何两个皇后都不能处于同一左下右上对角线
    for(int i = row - 1, j = col + 1; i >= 0 && j < board.size(); i--, j++){
        if(board[i][j] == 'Q')
            return false;
    }
    return true;
}

void solveNQueens(vector<string>& board, int row, vector<vector<string>>& results)
{
    // 递归遍历的结束条件，若最后一行已经正确摆放皇后则将该摆法放入解空间并返回
    if(row == board.size()){
        results.push_back(board);
        return;
    }
    // 每个阶段或每行逐个遍历可能的放置列位置
    for(int col = 0; col < board[row].size(); ++col){
    	// 跳过皇后会相互攻击的摆法，也即剪枝，提高效率
        if(isValid(board, row, col) == false)
            continue;
        // 前面已验证(row, col) 位置不会相互攻击，该位置放置皇后
        board[row][col] = 'Q';
        // 按照DFS 遍历规律，沿当前选择路径继续向下一阶段也即下一行递归，行号加一
        solveNQueens(board, row + 1, results);
        // 回退到上一阶段并将(row, col) 位置皇后从当前摆法移除，也即替换为空位
        board[row][col] = '.';
    }
}

void printQueue(vector<vector<string>>& results)
{
	// 如果没有满足要求的摆法，打印提示信息并返回
    if(results.empty()){
        cout << "There is no correct solution" << endl;
        return;
    }
	// 打印所有满足要求的摆法，每种摆法存储为vector<string>，n+1 为第几种摆法
    for(int n = 0; n < results.size(); ++n){
        cout << n + 1 << ":" << endl;
        for(const auto& str : results[n])
            cout << str << endl;
        cout << endl;
    }
}

int main(void)
{
    int n = 8;
    vector<vector<string>> results;
    vector<string> board(n, string(n, '.'));
    
    solveNQueens(board, 0, results);
    printQueue(results);

    return 0;
}