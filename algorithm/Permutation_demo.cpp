#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

// [Leetcode - 46] 全排列：给定一个 没有重复 数字的序列，返回其所有可能的全排列。
void permute(vector<int>& nums, vector<vector<int>>& results)
{
	// 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径、标记已选择元素
    static vector<int> path;
    static vector<bool> visited(nums.size(), false);
    // 递归遍历的结束条件，若满足结束条件则将该排列放入解空间并返回
    if(path.size() == nums.size()){
        results.push_back(path);
        return;
    }
    // 每个结点状态逐个遍历可能的选择分支
    for (int i = 0; i < nums.size(); ++i) {
        // 跳过前面已选择的分支，也即剪枝，提高效率
        if(visited[i] == true)
            continue;
        // 将分支nums[i] 添加到当前选择路径，并标记该元素已选择
        path.push_back(nums[i]);
        visited[i] = true;
        // 按照DFS 遍历规律，沿当前选择路径继续向下一阶段递归
        permute(nums, results);
        // 回退到上一阶段并将分支nums[i] 从当前选择路径移除，取消该元素的标记
        path.pop_back();
        visited[i] = false;
    }
}

// [Leetcode - 47] 全排列 II：给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
void permuteUnique(vector<int>& nums, vector<vector<int>>& results)
{
	// 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径、标记已选择元素
    static vector<int> path;
    static vector<bool> visited(nums.size(), false);
    // 递归遍历的结束条件，若满足结束条件则将该排列放入解空间并返回
    if(path.size() == nums.size()){
        results.push_back(path);
        return;
    }
    // 每个结点状态逐个遍历可能的选择分支
    for (int i = 0; i < nums.size(); ++i) {
        // 跳过前面已选择的分支，也即剪枝，提高效率
        if(visited[i] == true)
            continue;
        // 若元素nums[i] 与nums[i-1] 相等，且nums[i-1] 已取消标记，再重新选择重复元素nums[i] 将会获得重复排列，应跳过该选择
        if(i > 0 && nums[i] == nums[i-1] && visited[i-1] == false)
            continue;
        // 将分支nums[i] 添加到当前选择路径，并标记该元素已选择
        path.push_back(nums[i]);
        visited[i] = true;
        // 按照DFS 遍历规律，沿当前选择路径继续向下一阶段递归
        permuteUnique(nums, results);
        // 回退到上一阶段并将分支nums[i] 从当前选择路径移除，取消该元素的标记
        path.pop_back();
        visited[i] = false;
    }
}

void printResults(vector<vector<int>>& results)
{
	// 如果没有满足要求的解，打印提示信息并返回
    if(results.empty()){
        cout << "There is no correct solution." << endl;
        return;
    }
	// 打印所有满足要求的解，n+1 为第几个解
    for(int n = 0; n < results.size(); ++n){
        cout << n + 1 << ":\t";
        for(const auto elm : results[n])
            cout << elm << '\t';
        cout << endl;
    }
}

int main(void)
{
    int method;
    
    printf("leetcode-46 permute         : 1\n");
    printf("leetcode-47 permuteUnique   : 2\n");
    printf("Select  algorithm: ");
    scanf("%d", &method);

    vector<int> nums;
    vector<vector<int>> results;

    switch (method)
    {
    case 1:
        nums = {1, 2, 3, 4, 5};
        permute(nums, results);
        break;

    case 2:
        nums = {1, 3, 2, 3, 1, 2};
        sort(nums.begin(), nums.end());
        permuteUnique(nums, results);
        break;
    
    default:
        break;
    }
    
    printResults(results);

    return 0;
}