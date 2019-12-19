#include <iostream>
#include <list>
#include <algorithm>

template <typename T>
void printElements(const T& coll)
{
    for(auto iter = coll.begin(); iter != coll.end(); ++iter)
    {
        if(iter != coll.begin())
            std::cout << " <--> ";
        const auto& elem = *iter;
        std::cout << elem;
    }
    std::cout << std::endl;
}

void printLists(const std::list<int>& list1, const std::list<int>& list2)
{
    std::cout << "list1: ";
    printElements(list1);
    std::cout << "list2: ";
    printElements(list2);
    std::cout << std::endl;
}

int main(void)
{
    // create two empty lists
    std::list<int> list1, list2;

    // fill both lists with elements
    for(int i = 0; i < 6; ++i)
    {
        list1.push_back(i);
        list2.push_front(i);
    }
    printLists(list1, list2);

    // insert all elements of list1 before the first element with value 3 of list2
    list2.splice(std::find(list2.begin(), list2.end(), 3), list1);
    printLists(list1, list2);

    // move first element of list2 to the end
    list2.splice(list2.end(), list2, list2.begin());
    printLists(list1, list2);

    // sort second list, assign to list1 and remove duplicates
    list2.sort();
    list1 = list2;
    list2.unique();
    printLists(list1, list2);

    // merge both sorted lists into the first list
    list1.merge(list2);
    printLists(list1, list2);

    return 0;
}