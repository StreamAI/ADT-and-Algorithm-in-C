#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

int main(void)
{
    std::set<int, std::greater<int>> set1;

    // insert elements in random order
    set1.insert({4, 3, 5, 1, 6, 2});
    set1.insert(5);

    // print all elements
    for(int elem : set1)
        std::cout << elem << ' ';
    std::cout << std::endl;

    // insert 4 again and process return value
    auto status = set1.insert(4);
    if(status.second)
        std::cout << "4 inserted as element " << std::distance(set1.begin(), status.first) + 1 << std::endl;
    else
        std::cout << "4 already exists" << std::endl;
    
    // assign elements to another set with ascending order
    std::multiset<int> set2(set1.cbegin(), set1.cend());

    // print all elements of the copy using stream iterators
    std::copy(set2.cbegin(), set2.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // insert elements
    set2.insert(4);

    // remove all elements up to element with value 3
    set2.erase(set2.begin(), set2.find(3));

    // remove all elements with value 5
    int num = set2.erase(5);
    std::cout << num << " element(s) removed" << std::endl;

    // print all elements
    std::copy(set2.cbegin(), set2.cend(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    return 0;
}