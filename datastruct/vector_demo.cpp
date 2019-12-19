#include <iostream>
#include <vector>
#include <string>
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
    // create empty vector for strings
    std::vector<std::string> sentence;
    
    // reserve memory for five elements to avoid reallocation
    sentence.reserve(5);
    
    // append some elements
    sentence.push_back("Hello,");
    sentence.insert(sentence.end(), {"how", "are", "you", "?"});
    
    // print elements and some attribute value
    printElements(sentence);
    std::cout << "max_size: " << sentence.max_size() << std::endl;
    std::cout << "size:     " << sentence.size() << std::endl;
    std::cout << "capacity: " << sentence.capacity() << std::endl;
    std::cout << "address:  " << &sentence.at(0) << std::endl;
    
    //swap elements
    std::swap(sentence[1], sentence[3]);
    
    // insert elements before elements "?"
    sentence.insert(std::find(sentence.begin(), sentence.end(), "?"), "always");
    
    // assign "!" to the last elements
    sentence.back() = "!";
    
    // print elements and some attribute value
    printElements(sentence);
    std::cout << "size:     " << sentence.size() << std::endl;
    std::cout << "capacity: " << sentence.capacity() << std::endl;
    std::cout << "address: " << &sentence.at(0) << std::endl;
    
    // delete last two elements
    sentence.pop_back();
    sentence.pop_back();
    
    // shrink capacity
    sentence.shrink_to_fit();
    
    // print elements and some attribute value
    printElements(sentence);
    std::cout << "size:     " << sentence.size() << std::endl;
    std::cout << "capacity: " << sentence.capacity() << std::endl;
    std::cout << "address:  " << &sentence.at(0) << std::endl;

    return 0;
}