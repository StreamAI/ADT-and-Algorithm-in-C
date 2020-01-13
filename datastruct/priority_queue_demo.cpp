#include <iostream>
#include <queue>

int main(void)
{
    std::priority_queue<float> pq;

    //insert three elements into the priority queue
    pq.push(66.6);
    pq.push(22.2);
    pq.push(44.4);

    // read and print two elements
    std::cout << pq.top() << ' ';
    pq.pop();
    std::cout << pq.top() << std::endl;
    pq.pop();

    //insert three more elements
    pq.push(11.1);
    pq.push(55.5);
    pq.push(33.3);

    // skip one element
    pq.pop();

    // pop and print remaining elements
    while (!pq.empty())
    {
        std::cout << pq.top() << ' ';
        pq.pop();
    }
    std::cout << std::endl;

    return 0;
}