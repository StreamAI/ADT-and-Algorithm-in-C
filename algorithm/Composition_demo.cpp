#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

// [Leetcode-77] 组合： 给定两个整数 n 和 k，返回 1 … n 中所有可能的 k 个数的组合。
void combine(vector<int>& nums, int k, int index, vector<vector<int>>& results)
{
    // 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径
    static vector<int> path;
    // 递归遍历的结束条件，若满足结束条件则将该组合放入解空间并返回
    if(path.size() == k){
        results.push_back(path);
        return;
    }
    // 每个结点状态逐个遍历可能的选择分支，变量 i 初始值为index，且在每次递归增加 1，保证只选择后续分支
    for(int i = index; i < nums.size(); ++i){
        // 将分支nums[i] 添加到当前选择路径
        path.push_back(nums[i]);
        // 按照DFS 遍历规律，沿当前选择路径继续向下一阶段递归，变量 i+1 保证后续只选择分支nums[i] 后面的元素
        combine(nums, k, i + 1, results);
        // 回退到上一阶段并将分支nums[i] 从当前选择路径移除
        path.pop_back();
    }
}

// [Leetcode-78] 子集：给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（多叉递归树解法）。
void subsets_nTree(vector<int>& nums, int index, vector<vector<int>>& results)
{
    static vector<int> path;
    // 递归遍历所有结点，并将每个结点构成的组合放入解空间
    results.push_back(path);
    // 每个结点状态逐个遍历可能的选择分支，变量 i 初始值为index，且在每次递归增加 1，保证只选择后续分支
    for(int i = index; i < nums.size(); ++i){
        path.push_back(nums[i]);
        subsets_nTree(nums, i + 1, results);
        path.pop_back();
    }
}

// [Leetcode-90] 子集 II：给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（多叉递归树解法）。
void subsetsWithDup_nTree(vector<int>& nums, int index, vector<vector<int>>& results)
 {
    // 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径
    static vector<int> path;
    // 递归遍历所有结点，并将该组合放入解空间
    results.push_back(path);
    // 每个结点状态逐个遍历可能的选择分支，变量 i 初始值为index，且在每次递归增加 1，保证只选择后续分支
    for(int i = index; i < nums.size(); ++i){
        // 若元素nums[i] 与nums[i-1] 相等，且nums[i] 不是当前阶段首个选择分支，则会得到重复组合，应跳过该选择
        if(i > index && nums[i] == nums[i - 1])
            continue;
        // 将分支nums[i] 添加到当前选择路径
        path.push_back(nums[i]);
        // 按照DFS 遍历规律，沿当前选择路径继续向下一阶段递归，变量 i+1 保证后续只选择分支nums[i] 后面的元素
        subsetsWithDup_nTree(nums, i + 1, results);
        // 回退到上一阶段并将分支nums[i] 从当前选择路径移除
        path.pop_back();
    }
}


// [Leetcode-78] 子集：给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（二叉递归树解法）。
void subsets_binary(vector<int>& nums, int index, vector<vector<int>>& results)
{
    // 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径
    static vector<int> path;
    // 递归遍历的结束条件，若递归到叶子结点则将该组合放入解空间并返回
    if(index == nums.size()){
        results.push_back(path);
        return;
    }
    // 选择当前元素nums[index]
    path.push_back(nums[index]);
    subsets_binary(nums, index + 1, results);
    path.pop_back();
    // 不选择当前元素nums[index]
    subsets_binary(nums, index + 1, results);
}

// [Leetcode-90] 子集 II：给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（二叉递归树解法）。
void subsetsWithDup_binary(vector<int>& nums, int index, vector<vector<int>>& results)
{
    // 使用static 变量只在第一次定义并初始化，后续递归调用不会再重新定义或初始化，用于记录选择路径
    static vector<int> path;
    static vector<bool> visited(nums.size(), false);
    // 递归遍历的结束条件，若递归到叶子结点则将该组合放入解空间并返回
    if(index == nums.size()){
        results.push_back(path);
        return;
    }
    // 选择当前元素nums[index]，剪除重复组合的选择分支，注意括号里面的条件取反（前面的逻辑非！）
    if(!(index > 0 && nums[index] == nums[index - 1] && visited[index-1] == false)){
        path.push_back(nums[index]);
        visited[index] = true;
        subsetsWithDup_binary(nums, index + 1, results);
        path.pop_back();
        visited[index] = false;
    }
    // 不选择当前元素nums[index]  
    subsetsWithDup_binary(nums, index + 1, results);
}

// [Leetcode - 39] 组合总和：给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
void combinationSum(vector<int>& candidates, int target, int index, vector<vector<int>>& results){
    // 使用static 变量用于记录当前选择的组合
    static vector<int> path;
    // 递归遍历的结束条件，若递归到叶子结点或者组合总和满足约束条件则返回
    if(index == candidates.size()){
        // 若组合总和正好等于target，则将该组合保存到解空间并返回
        if(target == 0)
            results.push_back(path);
        return;
    }
    //不选择元素candidates[i]，target 不变，索引index 加一
    combinationSum(candidates, target, index + 1, results);
    //选择元素candidates[i]，target 减去该元素值，由于可以重复选择该元素，索引index 不变
    if(target - candidates[index] >= 0){
        path.push_back(candidates[index]);
        combinationSum(candidates, target - candidates[index], index, results);
        path.pop_back();
    }
}

void combinationSum2(vector<int>& candidates, int target, int index, vector<vector<int>>& results){
    // 使用static 变量用于记录当前选择的组合
    static vector<int> path;
    static vector<bool> visited(candidates.size(), false);
    // 递归遍历的结束条件，若递归到叶子结点或者组合总和满足约束条件则返回
    if(index == candidates.size()){
        // 若组合总和正好等于target，则将该组合保存到解空间并返回
        if(target == 0)
            results.push_back(path);
        return;
    }
    //不选择元素candidates[i]，target 不变，索引index 加一
    combinationSum2(candidates, target, index + 1, results);
    //选择元素candidates[i]，target 减去该元素值，由于每个元素只能选择一次，索引index 加一
    if(target - candidates[index] >= 0){
        if(index > 0 && candidates[index] == candidates[index - 1] && visited[index-1] == false)
            return;
        
        path.push_back(candidates[index]);
        visited[index] = true;
        combinationSum2(candidates, target - candidates[index], index + 1, results);
        path.pop_back();
        visited[index] = false;
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
    
    printf("leetcode-77 combine                 : 1\n");
    printf("leetcode-78 subsets_nTree           : 2\n");
    printf("leetcode-90 subsetsWithDup_nTree    : 3\n");
    printf("leetcode-78 subsets_binary          : 4\n");
    printf("leetcode-90 subsetsWithDup_binary   : 5\n");
    printf("leetcode-39 combinationSum          : 6\n");
    printf("leetcode-40 combinationSum2         : 7\n");
    printf("Select  algorithm: ");
    scanf("%d", &method);

    vector<int> nums;
    int k, target;
    vector<vector<int>> results;

    switch (method)
    {
    case 1:
        nums = {1, 2, 3, 4};
        k = 2;
        combine(nums, k, 0, results);
        break;

    case 2:
        nums = {1, 2, 3};
        subsets_nTree(nums, 0, results);
        break;

    case 3:
        nums = {1, 2, 2};
        sort(nums.begin(), nums.end());
        subsetsWithDup_nTree(nums, 0, results);
        break;

    case 4:
        nums = {1, 2, 3};
        subsets_binary(nums, 0, results);
        break;

    case 5:
        nums = {1, 2, 2};
        sort(nums.begin(), nums.end());
        subsetsWithDup_binary(nums, 0, results);
        break;

    case 6:
        nums = {2, 3, 6, 7};
        target = 7;
        combinationSum(nums, target, 0, results);
        break;


    case 7:
        nums = {10, 1, 2, 7, 6, 1, 5};
        target = 8;
        sort(nums.begin(), nums.end());
        combinationSum2(nums, target, 0, results);
        break;
    
    default:
        break;
    }
    
    printResults(results);


    return 0;
}