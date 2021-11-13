#include <iostream>
#include <string>
using namespace std;
template <typename ty> //using template to implement array based stacks functionlaity
// class Stack
class Stack
{

    // private fields
private:
    ty* stack;
    int top = -1;
    int size;
    int n = 100;

    // public methods
public:
    // constructor
    Stack() {
        size = 100;
        stack = new ty[100];
    }
    //paramterized constructor
    Stack(int n)
    {
        size = n;
        stack = new ty[size];
    }

    // push method to insert elements into the stack
    void push(ty element) {
        if (!this->isFull()) {
            stack[++top] = element;
        }
        else {
            std::cout << "Stack Overflow!" << endl;
        }
    }

    // pop method to remove and return top most element from the stack
    ty pop() {
        if (!this->isEmpty()) {
            ty element = stack[top];
            stack[top--].~ty();
            return element;
        }
        else {
    
           cout << "Stack is Empty!" << endl;
           return '0';
        }
    }

    // method to check if the stack is empty
    bool isEmpty()
    {
        return (top == -1);
    }

    // method to check if the stack is full
    bool isFull()
    {
        return (top == size - 1);
    }

    // method to clear the stack
    void clear()
    {
        while (!this->isEmpty())
        {
            this->pop();
        }
    }

    // method to return the top most element of the stack
    ty Peak()
    {
        if (!isEmpty())
        {
            return stack[top];
        }
        return '0';
    }
}; //stack class ends here
//a function to check validity of the expression entered
bool validityCheck(string expression)
{
    bool valid = true; //bbolean variable
    Stack <char> stack1(expression.length()); //creating object
    // for loop to traverse over the expression string
    for (int i = 0; i < expression.length(); i++)
    { // for loop starts
        // check for opening brackets
        if (expression[i] == '(' || expression[i] == '{' || expression[i] == '[')
        { // first if starts
            stack1.push(expression[i]);
            continue;
        } // first if ends
        // check for closing brackets
        else if (expression[i] == ')' || expression[i] == '}' || expression[i] == ']')
        {
            char OpeningToken = ' '; 
            //using switch case to check opening and closing of brackets
            switch (expression[i]) // assign appropriate opening bracket
            {
            
            case ')':
                OpeningToken = '(';
                break;
            case '}':
                OpeningToken = '{';
                break;
            case ']':
                OpeningToken = '[';
                break;
            }
            if (OpeningToken == stack1.Peak()) //if character token matches the character at the peak of stack, pop it out
            {
                stack1.pop();
            }
            else
            {
                //esle validity is set to false
                valid = false;
                break;
            }
        }
    }
    if (!stack1.isEmpty())
    {
        valid = false;
    }

    return valid; //returns bool 
}