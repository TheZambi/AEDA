# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> stackPrincip;
    stack<T> stackMin;
public:

	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const
{
	return stackPrincip.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    if(!stackPrincip.empty()) {
        *novo = stackPrincip.top();
    }
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{

    stackMin.pop();
    stackPrincip.pop();

}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    stackPrincip.push(val);
    if(stackMin.empty())
        stackMin.push(val);
    else {
        if(val <= stackMin.top())
            stackMin.push(val);
        else
            stackMin.push(stackMin.top());
    }
}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    if(!stackMin.empty()) {
        *novo = stackMin.top();
    }
    return *novo;
}

