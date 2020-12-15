#include<iostream>
#include<string>
#include<regex>

using namespace std;

static void regex_search_demo(void)
{
    string data1("XML tag: <tag-name>the value</tag-name>.");		// 要查找匹配的数据1
    regex reg1("<(.*)>(.*)</(\\1)>");			// 定义正则表达式1，最后的转义字符\\1 实际上是'\1'，表示跟第一组相同
    bool found = regex_match(data1, reg1);		// 正则匹配整个字符序列
    cout << "regex_match result:    " << (found ? "found" : "not found") << endl;

    regex reg2(".*<(.*)>(.*)</(\\1)>.*");		// 定义正则表达式2
    found = regex_match(data1, reg2);			// 正则匹配整个字符序列
    cout << "regex_match result:    " << (found ? "found" : "not found") << endl;

    found = regex_search(data1, reg1);			// 正则查找部分字符序列
    cout << "regex_search result:   " << (found ? "found" : "not found") << endl;
    cout << endl;

    smatch mres;		// 保存匹配的返回结果，若匹配结果为string object 则使用smatch 类型（wstring 对应wsmatch）
    					//若匹配结果为C-string 则使用cmatch 类型（wchar_t 对应wcmatch）
    found = regex_search(data1, mres, reg1);	// 保存模式匹配结果的正则查找
    if(found == true) {
        cout << "mres.size():           " << mres.size() << endl;			// 匹配对象的个数，如下图所示data1 共有4 个匹配对象mres[0] ~ mres[3]
        cout << "mres.str():            " << mres.str() << endl;			// 打印整个匹配结果的字符序列，可使用str(n) 获得对应部分的匹配字符序列，n 对应下图中0 ~ 3
        cout << "mres.length():         " << mres.length() << endl;			// 打印整个匹配结果的字符数，可使用length(n) 获得对应部分的字符数量，n 对应下图中0 ~ 3
        cout << "mres.position():       " << mres.position() << endl;		// 打印整个匹配结果的起始位置，可使用position(n) 获得对应部分的匹配字符位置，n 对应下图中0 ~ 3
        cout << "mres.prefix().str():   " << mres.prefix().str() << endl;	// 表示第一个匹配合格的字符前方的所有字符
        cout << "mres.suffix().str():   " << mres.suffix().str() << endl;	// 表示最后一个匹配合格的字符后方的所有字符
        cout << endl;
    }

    string data2 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// 要查找匹配的数据2
    auto pos = data2.cbegin();					// 保存要查找数据的起始位置
    while (regex_search(pos, data2.cend(), mres, reg1)) {
        cout << "match result:      	" << mres.str() << endl;	// 打印匹配结果
        cout << "tag-name:          	" << mres.str(1) << endl;	// 打印匹配结果的第一组，也即下图中的m[1]
        cout << "the value:         	" << mres.str(2) << endl;	// 打印匹配结果的第二组，也即下图中的m[2]
        pos = mres.suffix().first;		// 将查找数据的起始位置设置为该匹配结果的下一个字符
    }
}

static void regex_replace_demo(void)
{
    string data1 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// 要查找匹配的数据1
    cout << "The original data:" << endl << data1 << endl;
    regex reg1("<(.*)>(.*)</(\\1)>");			// 定义正则表达式1，最后的转义字符\\1 实际上是'\1'，表示跟第一组相同
    string repl1 = R"(<$1 value = "$2"/>)";		// 要将匹配结果替换成的字符串形式，R 表示raw string 可省略转义字符
    											// $1 和$2 表示匹配的子表达式，同上图中的m[1] 和m[2]（也即tag-name 和the value）
    string res1 = regex_replace(data1, reg1, repl1);	// 将匹配结果替换为repl1 的形式
    cout << "After replacement data:" << endl << res1 << endl;
}

static void regex_token_separator_demo(void)
{
    string data1 = "Hello world, friend\t of mine!\n";      // 要分割的字符串1
    regex sep("[ \t\n]*[,;.:! ][ \t\n]*");              // 使用正则表达式定义分隔符,;.:!space，前后允许有若干space\t\n
    // 将分隔符定义为匹配对象，token_iterator 可取匹配子序列之间的内容，相当于实现了语汇切分器token separator 的功能
    sregex_token_iterator pos1(data1.cbegin(), data1.cend(), sep, -1);  // 最后一个参数 -1 表示对每个匹配子序列之间的子序列感兴趣
                                                                // 0 表示对整个匹配序列感兴趣相当于m[0]，n 表示对第n 个匹配子序列感兴趣相当于m[n]
    sregex_token_iterator end;
    for (; pos1 != end; ++pos1)
        cout << "token:     " << *pos1 << endl;         // 输出被token separator 切分出的每个token
    cout << endl;

    string data2 =  "<person>\n"
                    "<first>Nico</first>\n"
                    "<last>Joson</last>\n"
                    "</person>\n";				// 要查找匹配的数据2
    regex reg1("<(.*)>(.*)</(\\1)>");			// 定义正则表达式1
    sregex_token_iterator pos2(data2.cbegin(), data2.cend(), reg1, {0, 2}); // 最后一个参数{0,2}表示对整个匹配序列和第2个匹配子序列感兴趣，也即m[0]和m[2]
    for (; pos2 != end; ++pos2)
        cout << "match:     " << pos2->str() << endl;      // 输出感兴趣的匹配结果
    cout << endl;
}

int main(int argc, char* argv[])
{ 
    regex_search_demo();
    cout << endl;
    regex_replace_demo();
    cout << endl;
    regex_token_separator_demo();
    cout << endl;
    
    return 0;
}