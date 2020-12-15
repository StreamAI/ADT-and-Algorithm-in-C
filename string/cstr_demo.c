#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void numtostr_demo(void)
{
    // 整数值转换为单字节字符串
    char buf1[32];
    long int a = -684565764;
    sprintf(buf1, "%ld", a);
    printf("The integer numeric string format: %s\n", buf1);

    // 浮点值转换为单字节字符串
    char buf2[32];
    double b = -5365.567246674;
    sprintf(buf2, "%f", b);
    printf("Floating-point value string format: %s\n", buf2);

    // 字符串转换为整数值或浮点值
    long int aa = strtol(buf1, NULL, 10);
    double bb = strtod(buf2, NULL);
    printf("The integer value = %ld, Floating point value = %f\n", aa, bb);
}

static void cstr_insert_demo(void)
{
    // 在str 中间插入子串str2
    char str1[20] = "How you?";
    char str2[20] = " are ";
    int r1 = strcat_s(str2, sizeof(str2), str1 + 4);
    printf("str2: %s\t\t,r1 = %s\n", str2, strerror(r1));	//这里使用制表符\t是为了对齐
    str1[3] = '\0';
    int r2 = strcat_s(str1, sizeof(str1), str2);
    printf("str1: %s\t,r2 = %s\n", str1, strerror(r2));

    // 若追加字符数量超出str 缓冲区则返回非零错误码并写入'\0'到str[0]
    char str3[] = "GoodBye!";
    int r3 = strncat_s(str1, sizeof(str1), str3, strlen(str3));
    printf("str1: %s\t\t\t,r3 = %s\n", str1, strerror(r3)); //使用strerror函数获取errno对应的描述信息
}

static void cstr_modify_demo(void)
{
    // 使用strncpy修改str中间部分字符不自动添加'\0'，使用strncpy_s修改str2中间部分字符会自动添加'\0'
    char str[20] = "www.google.com";
    char str2[20] = "www.bing.com";
    strncpy(str + 4, str2 + 4, 4);
    printf("str: %s\t,str2: %s\n", str, str2);
    int r1 = strncpy_s(str2 + 4, sizeof(str2) - 4, str + 4, 5);
    printf("str: %s\t,str2: %s\t,r1 = %d\n", str, str2, r1);

    // memmove可处理内存重叠的情况，使用memset将str2中间的'\0'替换为' '则会与后面未被覆盖的字符连起来
    int r2 = memmove_s(str + 8, sizeof(str2) - 8, str + 10, 6);
    memset(str2 + 9, ' ', 1);
    printf("str: %s\t,str2: %s\t,r2 = %d\n", str, str2, r2);
}

static void cstr_find_demo(void)
{
    const char* str = "hello world, friend of mine!";
    const char* sep = " ,!";

    // 在str 中全匹配子字符串
    char* pos1 = strstr(str, "friend");
    (pos1 == NULL) ? puts("substr1: Not found") : printf("Found substr1 at position: %ld\n", pos1 - str);
    char* pos2 = strstr(str, "friendly");
    (pos2 == NULL) ? puts("substr2: Not found") : printf("Found substr2 at position: %ld\n", pos2 - str);

    // 统计str 中的单词数量
    unsigned int cnt = 0;
    do {
       str = strpbrk(str, sep); // 寻找分隔符
       if(str) str += strspn(str, sep); // 跳过分隔符
       ++cnt; // 增加单词计数
    } while(str != NULL && *str != '\0');
    printf("There are %d words\n", cnt);
}

static void cstr_delim_demo(void)
{
    char str[] = "Hello world, friend of mine!";
    const char delim[] = " ,!";		// 分隔符集合
    char* next_token = NULL;
    printf("Parsing the input string '%s'\n", str);
    char* token = strtok_s(str, delim, &next_token);	// 首次调用
    printf("Token:\t\tNext_token:\n");
    while(token != NULL) {
        printf("%s\t\t%s\n", token, next_token);	// 分别输出token 和next_token 字符串，更方便理解nect_token 参数作用
        token = strtok_s(NULL, delim, &next_token);	// 后继调用首参数传入空指针
    }
    
 	// 输出字符串全部字符，可看到原字符串中的分隔符均被替换为了'\0'
    printf("Contents of the input string now: '");
    for(size_t n = 0; n < sizeof(str); ++n)
        (str[n] != '\0') ? putchar(str[n]) : fputs("\\0", stdout);
    puts("'");
}

int main(void)
{
    numtostr_demo();
    puts("");
    cstr_insert_demo();
    puts("");
    cstr_modify_demo();
    puts("");
    cstr_find_demo();
    puts("");
    cstr_delim_demo();
    puts("");

    return 0;
}