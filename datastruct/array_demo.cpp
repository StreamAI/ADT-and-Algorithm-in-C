#include <iostream>
#include <array>
#include <algorithm>

template <typename T>
void printElements(const T& coll)
{
    for(auto iter = coll.begin(); iter != coll.end(); ++iter)
    {
        const auto& elem = *iter;
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main(void)
{
    // create array with 10 ints
    std::array<int, 10> a = {31, 22, 19, 47};
    printElements(a);
    // modify last two elements
    a.back() = 99;  
    a[a.size() - 2] = 42;
    printElements(a);
    // sort the array elements
    std::sort(a.begin(), a.end());
    printElements(a);

    return 0;
}