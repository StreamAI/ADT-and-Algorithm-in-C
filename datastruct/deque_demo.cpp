#include <iostream>
#include <deque>
#include <string>
#include <algorithm>

template <typename T>
void printElements(const T& coll)
{
    for(auto iter = coll.begin(); iter != coll.end(); ++iter)
    {
        const auto& elem = *iter;
        std::cout << elem << "\n";
    }
    std::cout << std::endl;
}

int main(void)
{
    // create empty deque of strings
    std::deque<std::string> coll;

    // insert several elements
    coll.assign(3, std::string("string"));
    coll.push_back("last string");
    coll.push_front("first string");
    printElements(coll);

    // remove first and last element
    coll.pop_front();
    coll.pop_back();

    // insert "another" into every element but the first
    for(int i = 1; i < coll.size(); ++i)
        coll[i] = "another " + coll.at(i);
    printElements(coll);

    //change size to four elements    
    coll.resize(4, "resized string"); 
    
    // sort the elements
    std::sort(coll.begin(), coll.end());
    printElements(coll);

    return 0;
}