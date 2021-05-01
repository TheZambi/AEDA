// CStack.h - uma Stack simples de inteiros implementada com arrays

#include <iostream>
#include <string>

using namespace std;

class CStack { 
    int top, d_size, *items;
public:
    CStack(int size) { top = -1; d_size = size; items = new int[size]; }
    ~CStack() { delete []items;} 
    bool empty() const { return top==-1; } 
    int size() const { return top+1; } 
    void push(int elem) { 
        if(size()==d_size) cerr << "Stack Full!\n";
        else { top++; items[top] = elem; }
    }
    void pop() { 
        if(this->empty()) cerr << "Empty stack\n";
        else top--;
    }
    int peek() const { 
        if(this->empty()) cerr << "Empty stack\n";
        else return items[top];
        return 0;
    }
    string toStr() const {
        stringstream oss;
        for(int i = size()-1; i>=0; i--)
        	oss << items[i] << " ";
        return oss.str();
    }
    void print() const { 
        cout << "Stack with " << size() << " elements: ";
        for(int i = size()-1; i>=0; i--)
            cout << items[i] << " ";
        cout << endl;
    }
    void adicionaN(int n)
	{  //Grupo 2 a)
        cout << top << endl << endl;
    	for(int i=0;i<n;i++)
    	    this->push(items[top]+1);
	}
	bool inverte4() 
	{   //Grupo 2 b)
        int val1, val2, val3, val4;
        if(top<3)
            return false;
        val1=items[top];
        this->pop();
        val2=items[top];
        this->pop();
        val3=items[top];
        this->pop();
        val4=items[top];
        this->pop();
        push(val1);
        push(val2);
        push(val3);
        push(val4);
    	return true;
	}	
}; 

