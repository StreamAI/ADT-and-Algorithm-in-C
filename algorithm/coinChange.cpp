#include<vector>
#include<algorithm>
#include<iostream>
using namespace std;

// // 回溯算法，穷举所有解后挑出最优解
void dfs_coins(vector<int>& coins, int amount, int idxCoin, int& minCoins)
{
	// 使用static 变量用于记录当前选择的组合
    static vector<int> path;
    // 遍历每种可能的组合，若满足目标总和则更新更少元素组合并返回
    if(amount == 0){
    	// 判断是否为更少的元素组合，遍历完所有组合后minCoins 保存的就是满足组合总和的最少元素数量
        if(path.size() < minCoins)
            minCoins = path.size();
        return;
    }
	// 每个结点状态逐个遍历可能的选择分支，由于每个元素数量不限，循环内递归调用参数idxCoin 不增加，以便选择相同的元素
    for(int i = idxCoin; i < coins.size(); ++i){
        if(amount - coins[i] >= 0){
            path.push_back(coins[i]);
            dfs_coins(coins, amount - coins[i], i, minCoins);
            path.pop_back();
        }      
    }
}

// 贪心算法，每次选择最快逼近目标值的分支
int greedy_coins(vector<int>& coins, int amount)
{
    if(amount < 0 || (coins.empty() && amount > 0))
        return -1;
    if(amount == 0)
        return 0;
    // 对各种面额按递减顺序排序，方便依次取最大面额、次大面额硬币
    sort(coins.begin(), coins.end(), greater<int>());
    int minCoins = 0;	// 最少硬币数量
    for (int i = 0; i < coins.size(); i++) {
        if(amount - coins[i] >= 0){
            minCoins += amount / coins[i];	// 取尽可能多数量当前能取的最大面额coins[i]
            amount = amount % coins[i];		// 选择amount / coins[i] 个数量的硬币后，更新剩余的目标总和
        }
    }
    // 若最后正好凑够目标总和，且选择了至少一枚硬币，则返回最少硬币数minCoin，否则返回-1
    if(amount != 0 || minCoins == 0)
        return -1;
    else
        return minCoins;
}

// 动态规划，最优子结构，未使用备忘录处理重叠子问题
int dp_coins(vector<int>& coins, int amount){
	// 边界约束条件，对应状态转移方程中的前两种情况
    if(amount < 0)
        return -1;
    else if(amount == 0)
        return 0;
    else{	// 状态转移方程中的第三种情况，也即递推公式，minCoins为当前阶段的最少硬币数，相当于f(amount)
        int minCoins = INT_MAX;
        for (int i = 0; i < coins.size(); i++) {
            if(amount - coins[i] >= 0){
            	// prevMin 相当于f(amount - coins[i])，对每个分支求 minCoins = min(minCoins, prevMin + 1)，相当于minCoins = min{amount - coins[0],...,amount - coins[i],...,amount - coins[coins.size() - 1] } + 1
                int prevMin = dp_coins(coins, amount - coins[i]);
                if(prevMin >= 0)
                    minCoins = min(minCoins, prevMin + 1);
            }
        }
        return minCoins == INT_MAX ? -1 : minCoins;
    }
}

// 动态规划，递归方式实现，也即状态转移方程法，使用备忘录处理了重叠子问题
int dp_memo_coins(vector<int>& coins, int amount, vector<int>& memo){
    if(amount < 0)
        return -1;
    else if(amount == 0)
        return 0;
    // 如果备忘录中已有子问题的解，则直接查表返回解
    if(memo[amount] != INT_MAX)
        return memo[amount];
    else{   // 若备忘录中没有子问题的解，则求得解后将其保存到备忘录中
        int minCoins = INT_MAX;
        for (int i = 0; i < coins.size(); i++) {
            if(amount - coins[i] >= 0){
                int prevMin = dp_memo_coins(coins, amount - coins[i], memo);
                if(prevMin >= 0)
                    minCoins = min(minCoins, prevMin + 1);
            }
        }
        memo[amount] = minCoins < INT_MAX ? minCoins : -1;
        return memo[amount];
    }
}

// 动态规划，迭代方式实现，也即状态转移表法
int dp_iter_coins(vector<int>& coins, int amount)
{
    if(amount < 0 || (coins.empty() && amount > 0))
        return -1;
    if(amount == 0)
        return 0;
    // 递归解法中的备忘录，也可称为状态转移表，长度为amount + 1，初始值为大于amount 的值，递归解法备忘录初始化为INT_MAX，这里初始化为amount + 1 效果一样
    vector<int> dp_table(amount + 1, amount + 1);
    dp_table[0] = 0;	// 边界约束条件，也即f(0) = 0
	// 按照递推公式或者状态转移方程从前往后依次填表
    for(int s = 1; s <= amount; s++){
        for (int i = 0; i < coins.size(); i++)
            if(s - coins[i] >= 0)
                dp_table[s] = min(dp_table[s], dp_table[s - coins[i]] + 1);            
    }
    return dp_table[amount] > amount ? -1 : dp_table[amount];
}

int main(void)
{
    int method;
    
    printf("leetcode-322 dfs_coins solution     : 1\n");
    printf("leetcode-322 greedy_coins solution  : 2\n");
    printf("leetcode-322 dp_coins solution      : 3\n");
    printf("leetcode-322 dp_memo_coins solution : 4\n");
    printf("leetcode-322 dp_iter_coins solution : 5\n");
    printf("Select  algorithm: ");
    scanf("%d", &method);

    vector<int> coins, memo;
    int amount;
    int minCoins;

    switch (method)
    {
    case 1:
        coins = {1, 2, 5};
        amount = 11;
        minCoins = INT_MAX;
        dfs_coins(coins, amount, 0, minCoins);
        minCoins = minCoins < INT_MAX ? minCoins : -1;
        break;

    case 2:
        coins = {1, 5, 11};
        amount = 15;
        minCoins = greedy_coins(coins, amount);
        break;

    case 3:
        coins = {1, 5, 11};
        amount = 15;
        minCoins = dp_coins(coins, amount);
        break;

    case 4:
        coins = {1, 5, 11};
        amount = 15;
        memo.resize(amount + 1, INT_MAX);
        minCoins = dp_memo_coins(coins, amount, memo);
        break;

    case 5:
        coins = {1, 5, 11};
        amount = 15;
        minCoins = dp_iter_coins(coins, amount);
        break;
    
    default:
        break;
    }
    
    cout << minCoins << endl;

    return 0;
}