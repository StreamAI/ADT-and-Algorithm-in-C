#include <iostream>
#include <stack>

int main(void)
{
    std::stack<int> st;

    // push three elements into the stack
    st.push(2);
    st.push(3);
    st.push(5);

    // pop and print two elements from the stack
    std::cout << st.top() << " ";
    st.pop();
    std::cout << st.top() << " ";
    st.pop();
    std::cout << std::endl;

    // modify top element;
    st.top() = 77;

    // push two new elements
    st.push(7);
    st.push(11);

    // pop one element without processing it
    st.pop();

    // pop and print remaining elements
    while (!st.empty())
    {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;

    return 0;
}