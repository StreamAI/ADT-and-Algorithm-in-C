#include <iostream>
#include <unordered_set>

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
    // create and initialize unordered set
    std::unordered_set<int> uset1 = {1, 2, 3, 5, 7, 11, 13, 17, 19, 77};

    // print all elments
    printElements(uset1);

    // insert some additional elements, might cause rehash
    uset1.insert({-1, 17, 33, -11, 17, 19, 1, 13});
    printElements(uset1);

    // remove element with specific value
    uset1.erase(33);
    printElements(uset1);

    // check if value 19 is in the set
    if(uset1.find(19) != uset1.end())
        std::cout << "19 is available" << std::endl;

    // remove all negative values
    std::unordered_set<int>::iterator pos;
    for(pos = uset1.begin(); pos != uset1.end(); ){
        if(*pos < 0)
            pos = uset1.erase(pos);
        else
            pos++;
    }
    printElements(uset1);

    // assign elements to another unordered_multiset
    std::unordered_multiset<int> uset2(uset1.cbegin(), uset1.cend());

    // insert some additional elements, might cause rehash
    uset2.insert({-1, 17, 33, -11, 17, 19, 1, 13});
    printElements(uset2);
    
    // remove all elements with specific value
    uset2.erase(17);

    // remove one of the elements with specific value
    auto pos2 = uset2.find(13);
    if(pos2 != uset2.end())
        uset2.erase(pos2);
    printElements(uset2); 

    return 0;
}