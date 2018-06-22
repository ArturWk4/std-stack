#include <iostream>
#include <stdexcept>


template<class T>
class stack
{
public:
    using value_type = T;
    using reference = T&;
    using size_type = std::size_t;

    struct Node
    {
        Node* m_next;
        T m_data;

        Node(T data) : m_data(data) {};
        Node(T data, Node* next) : m_data(data), m_next(next) {};
    };

    stack() : m_top(nullptr), m_size(0) {};

    void push(T value);
    void pop();
    T& top();
    bool empty();
    size_type size();

private:
    Node* m_top;
    size_type m_size;
};

template<class T>
void stack<T>::push(T value)
{
    try
    {
        if(m_top != nullptr)
        {
            Node* temp = new Node(value, m_top);
            m_top = temp;
        }
        else
        {
            m_top = new Node(value);
        }
        ++m_size;
    }
    catch(std::bad_alloc)
    {
        std::cout << "ERROR: bad allocation" << std::endl;
    }
}

template<class T>
void stack<T>::pop()
{
    if(m_top == nullptr)
        throw std::out_of_range("ERROR: Out of range!");

    Node* temp = m_top;
    m_top = m_top->m_next;
    delete temp;
    --m_size;
}

template<class T>
T& stack<T>::top()
{
    if(m_top == nullptr)
        throw std::out_of_range("ERROR: Out of range!");
    return m_top->m_data;
}
template<class T>
typename stack<T>::size_type stack<T>::size()
{
    return m_size;
}

template<class T>
bool stack<T>::empty()
{
    return m_size == 0;
}

int main()
{
    stack<int> my_stack;

    for(int i = 0; i < 20; ++i)
    {
        my_stack.push(i);
    }

    std::cout << "Size of stack: " << my_stack.size() << std::endl;
    std::cout << "Top element of the stack: " << my_stack.top() << std::endl;
    my_stack.pop();
    std::cout << "Top element after POP: " << my_stack.top();
    return 0;
}
