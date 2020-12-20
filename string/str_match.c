#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<stdint.h>
#include<limits.h>

#define STR_LEN     500000000
#define PAT_LEN     50000
#define CHAR_SIZE   128

static char* str_init(char* str, size_t n)
{
    str = malloc((n + 1) * sizeof(char));
    // 根据时间设置随机数种子，让每次生成的随机数不一样
    srand(time(NULL));
    // 随机生成包含26 各小写字母且长度为n 的字符串
    for(size_t i = 0; i < n; i++)
        // ASCII 字符集可显示字符为0x20 到0x7E 共95 个字符
        str[i] = 0x20 + rand() % 95;
    str[n] = '\0';

    return str;
}

static char* BF_match(const char* str, const char* pat)
{
    if(str == NULL || pat == NULL)
		return NULL;
 
	size_t i = 0, j = 0;
	while (str[i] != '\0' && pat[j] != '\0') {
		if (str[i] == pat[j]) {
			// 如果当前字符匹配成功，则主串与模式串游标都后移一位，对比下一个字符
			i++;
			j++;
		} else {
			// 如果当前字符不匹配，则将模式串游标移到首字符处，主串游标移到与模式串首字符对应的下一个位置
			i = i - j + 1;
			j = 0;
		}
	}
	// 匹配成功，返回模式串pat 在主串str 中的位置，否则返回 -1
	if (pat[j] == '\0')
		return (char *)(str + i - j);
	else
		return NULL;
}

static char* STR_match(const char* str, const char* pat)
{
    if(str == NULL || pat == NULL)
		return NULL;

    size_t pLen = strlen(pat);
    const char *pos = str;
    // 先找到主串与模式串首字符匹配的位置，找不到则返回空指针
    while ((pos = strchr(pos, pat[0])) != NULL) {
        // 主串与模式串首字符匹配，则继续比较后面的pLen - 1 个字符
        if(strncmp(pos, pat, pLen) == 0)
            return (char *) pos;    // 如果匹配成功，则返回主串匹配首字符指针
        ++pos;  // 若匹配失败，则主串游标后移一位，继续查找与模式串首字符匹配的位置
    }

    return NULL;
}

static size_t* Roll_hash(const char* str, const char* pat, const size_t pLen, const size_t sNum)
{
    // 为各子串及其模式串哈希值分配存储空间，hash[sNum]存储模式串哈希值，故分配sNum + 1 个元素
    size_t* hash = malloc((sNum + 1) * sizeof(size_t));
    if(hash == NULL) return NULL;
    size_t sHash = 0, pHash = 0;
    // 哈希函数使用最简单的将各字符ASCII 值相加
    for (size_t i = 0; i < pLen; i++) {
        sHash += (size_t)str[i];
        pHash += (size_t)pat[i];
    }
    hash[0] = sHash % (SIZE_MAX - CHAR_MAX);         // 存储主串中第一个与模式串等长的子串哈希值，并取余以防超出类型极限
    hash[sNum] = pHash % (SIZE_MAX - CHAR_MAX);      // 存储模式串哈希值，对(SIZE_MAX - CHAR_MAX)取余，后面滚动计算哈希值时可保证不超限
    // 采用滚动哈希算法，主串中各子串哈希值都根据前一个哈希值计算得出，因hash[0] < (SIZE_MAX - CHAR_MAX)，后续哈希值不用取余也可保证不超限
    for (size_t j = 1; j < sNum; j++)
        hash[j] = hash[j - 1] - (size_t)str[j - 1] + (size_t)str[j - 1 + pLen];
    
    return hash;
}

static char* RK_match(const char* str, const char* pat)
{
    if(str == NULL || pat == NULL)
		return NULL;
    // 计算模式串长度，以及主串中与模式串等长的子串数量
    size_t pLen = strlen(pat);
    size_t sLen = strlen(str);
    size_t sNum = sLen - pLen + 1;
    if(sNum < 1) 
        return NULL;
    // 调用滚动哈希计算函数，计算模式串以及主串中与模式串等长的各子串哈希值
    size_t *hash = Roll_hash(str, pat, pLen, sNum);
    if(hash == NULL)
        return NULL;
    // 获取模式串哈希值
    size_t hPat = hash[sNum];
    // 主串中各子串哈希值与模式串哈希值相比较
    for (size_t i = 0; i < sNum; i++) {
        // 如果某子串哈希值与模式串哈希值相等，则继续逐字符比较
        if(hPat == hash[i]) {
            // 如果模式串与某主串相匹配，则返回主串中匹配首字符的指针
            if(strncmp(str + i, pat, pLen) == 0){
                free(hash);     // 释放为hash 数组分配的空间 
                return (char *) (str + i);
            }
        }
    }
    // 释放为hash 数组分配的空间
    free(hash);
    return NULL;
}

static int* GetNext_BF(const char* pat, const size_t pLen)
{
    // 为next 数组分配空间，并初始化为 0
    int* next = calloc(pLen, sizeof(int));
    if(next == NULL) return NULL;
	next[0] = -1;	// next 数组首元素设为 -1，方便区分首字符不匹配的情况
	// j 为模式串各前缀子串的后一个字符位置，k 为其前缀子串的最大可匹配长度
    for (int j = 2; j < pLen; j++) {
        // 从最大长度开始尝试匹配前缀子串和后缀子串
        for(int k = j - 1; k > 0; k--) {
            // 若匹配成功则将最大长度k 记入next 数组，若匹配失败k-1 继续尝试
            if(strncmp(pat, pat + (j - k), k) == 0) {
                next[j] = k;
                break;
            }
        }
    }
    return next;
}

static int* GetNext(const char* pat, const size_t pLen)
{
    // 为next 数组分配空间，并初始化为 0
    int* next = calloc(pLen, sizeof(int));
    if(next == NULL) return NULL;
	next[0] = -1;   // next 数组首元素为-1，用于区别其它位置匹配失败的情况
    // k 为模式串最大可匹配前缀子串首字符游标，初始值 -1 表示不存在，j 为模式串首字符游标
	int k = -1, j = 0;
	while (j < pLen - 1) {
		// 如果是新模式串首字符不匹配，或者新模式串字符pat[k]与新主串字符pat[j]匹配成功，则next[j+1] = k+1
		if (k == -1 || pat[j] == pat[k]) {
			    next[++j] = ++k;
		} else {
            // 如果新模式串非首字符pat[k]与新主串字符pat[j]匹配失败，则新模式串游标k 回退到next[k] 处
			k = next[k];
		}
	}
    return next;
}

static char* KMP_match(const char* str, const char* pat)
{
    if(str == NULL || pat == NULL)
		return NULL;

	long long pLen = strlen(pat);
    long long sLen = strlen(str);
    // 为next 数组分配空间，并计算next 数组元素值
    int *next = GetNext(pat, pLen);
    if(next == NULL) 
        return NULL;
    // 比较主串与模式串，主串游标 i 不回退，模式串游标 j 按next 数组值回退
	long long i = 0, j = 0;
	while (j < pLen && i < sLen) {	
		// 如果模式串首字符与主串不匹配，或者模式串字符pat[j]与主串字符str[i]匹配，则主串与模式串的游标都后移一位，继续比较下一个字符
		if (j == -1 || str[i] == pat[j]) {
			i++;
			j++;
		} else {
			// 如果模式串非首字符pat[j]与主串字符str[i]不匹配，则主串游标i 不变，模式串游标j 回退到next[j] 处
			j = next[j];
		}
	}
    // 释放为next 数组分配的空间
    free(next);
	//匹配成功，返回模式串pat 在文本串str 中的位置，否则返回-1
	if (j == pLen)
		return (char *)(str + i - j);
	else
		return NULL;
}

static int* GenerateBC(const char* pat)
{
    // 为bc 数组分配空间，并初始化为 -1
    int* bc = malloc(CHAR_SIZE * sizeof(int));
    if(bc == NULL)  return NULL;
    memset(bc, -1, CHAR_SIZE * sizeof(int));
    // bc 数组采用哈希映射的思路，存储模式串中各字符的下标，靠后的字符下标会覆盖先前相同的字符下标
    for(int i = 0; pat[i] != '\0'; ++i){
        int ascii = (int)pat[i];
        bc[ascii] = i;
    }
    
    return bc;
}

static char* BMH_match(const char* str, const char* pat)
{
    if(str == NULL || pat == NULL)
		return NULL;

	long long pLen = strlen(pat);
    long long sLen = strlen(str);
    int *bc = GenerateBC(pat);
    if(bc == NULL)
        return NULL;

	long long i = 0, j = pLen - 1;
	while (i <= sLen - pLen) {
        // 从模式串pat 末字符往前逐个比较，直到发现匹配失败的字符或者模式串匹配完
        for(j = pLen - 1; j >= 0; --j){
            if(str[i + j] != pat[j])
                break;
        }
        // 如果模式串匹配完了，说明模式串匹配成功，返回主串匹配首字符指针
        if(j < 0) {
            free(bc);   // 释放为bc 数组分配的空间
            return (char *)(str + i);
        }
        // BMH 与BM 不同之处，BM 从匹配失败字符确定移动距离，BMH 从模式串末字符确定移动距离，故将游标j 重新移回模式串末字符位置
        j = pLen - 1;
        // 模式串匹配失败，确定主串游标i 的移动距离，i 的移动距离至少 1 位
        if(bc[(int)str[i + j]] < j)
            i += j - bc[(int)str[i + j]];
        else
            i++;
	}
    // 释放为bc 数组分配的空间
    free(bc);
	return NULL;
}

static bool validate_match(const char* pos, const char* pat)
{
    bool res = false;
    if(pos != NULL && pat != NULL){
        int pLen = strlen(pat);
        if(strncmp(pos, pat, pLen) == 0)
            res = true;
    }

    if(res == true)
        printf("The string match was successful.\n\n");
    else
        printf("The string match failed.\n\n");

    return res;
}

int main(void)
{
    int method;
    
    printf("BF      match: 1\n");
    printf("STR     match: 2\n");
    printf("RK      match: 3\n");
    printf("KMP     match: 4\n");
    printf("BMH     match: 5\n");
    printf("strstr  match: 6\n");
    printf("Select  method: ");
    scanf("%d", &method);

    char *str, *pat, *pos;
    long long index;
    str = str_init(str, STR_LEN);
    // 使用随机数生成主串和模式串之间等待2 秒，由于使用当前时间作为随机数种子，有时间差可以让模式串与主串前面的随机字符不一致
#if defined (__linux__) // any linux distribution
    system("sleep 2");
#elif defined (_WIN32) // any windows system
    system("ping -n 2 127.0.0.1 > nul");
#endif
    pat = str_init(pat, PAT_LEN);
    printf("The length of the main string   : %lu\n", (size_t)STR_LEN);
    printf("The length of the pattern string: %lu\n\n", (size_t)PAT_LEN);
    
    clock_t start, end;
    double time;
    start = clock();
    switch (method)
    {
    case 1:
        pos = BF_match(str, pat);
        break;

    case 2:
        pos = STR_match(str, pat);
        break;

    case 3:
        pos = RK_match(str, pat);
        break;
    
    case 4:
        pos = KMP_match(str, pat);
        break;

    case 5:
        pos = BMH_match(str, pat);
        break;

    case 6:
        pos = strstr(str, pat);
        break;
    
    default:
        break;
    }
    end = clock();
    time = (double)(end - start) / (CLOCKS_PER_SEC / 1000);

    validate_match(pos, pat);
    index = (pos == NULL) ? -1 : (pos - str);
    printf("Match location: %lld\n\n", index);
    printf("Execution time: %.3lf ms.\n\n", time);

    free(str);
    return 0;
}