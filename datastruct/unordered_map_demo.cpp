#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>
#include <iomanip>

template <typename T>
void printUnorderedCell(const T& cell)
{
    // basic hash layout data
    std::cout << "size:             " << cell.size() << std::endl;
    std::cout << "buckets:          " << cell.bucket_count() << std::endl;
    std::cout << "load factor:      " << cell.load_factor() << std::endl;
    std::cout << "max load factor:  " << cell.max_load_factor() << std::endl;

    // elements per bucket
    std::cout << "data: " << std::endl;
    for(auto idx = 0; idx != cell.bucket_count(); ++idx){
        std::cout << " b[" << std::setw(2) << idx << "]: ";
        for(auto pos = cell.begin(idx); pos != cell.end(idx); ++pos)
            std::cout << "[" << pos->first << ", " << pos->second << "] ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(void)
{
    // create unordered_map as associative array
    std::unordered_map<std::string, float> stocks;
    stocks["BMW"] = 834.12;
    stocks["Daimler"] = 819.32;
    stocks["Siemens"] = 842.69;
    stocks["VM"] = 413.52;

    // print all elements
    printUnorderedCell(stocks);

    // modify max load factor, might cause rehash
    stocks.max_load_factor(0.7);
    stocks["Benz"] = stocks["Daimler"];
    printUnorderedCell(stocks);

    // create and initialize an unordered multimap as dictionary
    std::unordered_multimap<std::string, std::string> dicts = {
        {"day", "Tag"}, {"smart", "elegant"}, {"car", "Auto"}, 
        {"smart", "klug"}, {"car", "Tag"}, {"clever", "raffiniert"}
    };
    printUnorderedCell(dicts);

    return 0;
}