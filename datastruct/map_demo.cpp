#include <iostream>
#include <map>
#include <string>
#include <iomanip>

int main(void)
{
    // create map as associative array
    std::map<std::string, float> stocks;
    stocks["BMW"] = 834.12;
    stocks["Daimler"] = 819.32;
    stocks["Siemens"] = 842.69;

    // print all elements
    std::cout << std::left;
    for(auto pos = stocks.begin(); pos != stocks.end(); ++pos)
        std::cout << "stock: " << std::setw(12) << pos->first
                << "price: " << pos->second << std::endl;
    std::cout << std::endl;

    // assign and erase element
    stocks["Benz"] = stocks["Daimler"];
    stocks.erase("Daimler");

    // print all elements
    for(auto pos = stocks.begin(); pos != stocks.end(); ++pos)
        std::cout << "stock: " << std::setw(12) << pos->first
                << "price: " << pos->second << std::endl;
    std::cout << std::endl;

    // search an element with key "BMW"
    auto pos = stocks.find("BMW");
    if(pos != stocks.end())
        std::cout << "stock: " << std::setw(12) << pos->first
                << "price: " << pos->second << std::endl;
    std::cout << std::endl;

    // create multimap as dictionary
    std::multimap<std::string, std::string> dicts;

    // insert some elements in random order
    dicts.insert({{"day", "Tag"}, {"smart", "elegant"}, {"car", "Auto"}, 
                    {"smart", "klug"}, {"car", "Tag"}});
    
    // print all elements
    std::cout << ' ' << std::setw(18) << "english " << "german " << std::endl;
    std::cout << std::setfill('-') << std::setw(32) << "" << std::setfill(' ') << std::endl;
    for(const auto& elem : dicts)
        std::cout << ' ' << std::setw(18) << elem.first << elem.second << std::endl;
    std::cout << std::endl;

    // print all values for key "smart"
    std::string word("smart");
    std::cout << word << ": " << std::endl;
    for(auto pos = dicts.lower_bound(word); pos != dicts.upper_bound(word); ++pos)
        std::cout << "      " << pos->second << std::endl;
    std::cout << std::endl;
    
    // print all keys for values "Tag"
    word = ("Tag");
    std::cout << word << ": " << std::endl;
    for(const auto& elem : dicts){
        if(elem.second == word)
            std::cout << "      " << elem.first << std::endl;
    }
    std::cout << std::endl;

    return 0;
}