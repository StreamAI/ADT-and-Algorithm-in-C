#include <iostream>
#include <forward_list>
#include <string>
#include <algorithm>

template <typename T>
void printElements(const T& coll)
{
    for(auto iter = coll.begin(); iter != coll.end(); ++iter)
    {
        if(iter != coll.begin())
            std::cout << " --> ";
        const auto& elem = *iter;
        std::cout << elem;
    }
    std::cout << std::endl;
}

void printLists(const std::string& str, const std::forward_list<int>& list1, 
                                        const std::forward_list<int>& list2)
{
    std::cout << str << std::endl;
    std::cout << "list1: ";
    printElements(list1);
    std::cout << "list2: ";
    printElements(list2);
    std::cout << std::endl;
}

int main(void)
{
    // create two forward lists
    std::forward_list<int> list1 = {1, 2, 3, 4};
    std::forward_list<int> list2 = {77, 88, 99};
    printLists("Initial:", list1, list2);

    // insert new element at the beginning of list2
    list2.insert_after(list2.before_begin(), 99);
    list2.push_front(10);
    list2.insert_after(list2.before_begin(), {10, 11, 12, 13});
    printLists("Insert new element:", list1, list2);

    // insert all elements of list2 at the beginning of list1
    list1.insert_after(list1.before_begin(), list2.begin(), list2.end());
    printLists("List2 into list1:", list1, list2);

    // delete second element, and elements after element with value 99
    list2.erase_after(list2.begin());
    list2.erase_after(std::find(list2.begin(), list2.end(), 99), list2.end());
    printLists("Delete some elements:", list1, list2);

    // sort list1, assign it to list2, and remove duplicates
    list1.sort();
    list2 = list1;
    list2.unique();
    printLists("Sorted and unique:", list1, list2);

    // merge both sorted lists into list1
    list1.merge(list2);
    list1.unique();
    printLists("Merged:", list1, list2);

    return 0;
}