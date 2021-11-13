#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
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
//function to perform operations while evaluating the expression
double operation(double a, double b, char op) {
    //using switch case 
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    default:
        return 0;
    }
} //function ends here

//function that sets the precidence of the operators
int precidence(char character) {
    //^ is set with with higher precidence i.e. followed by / and *, + and -
    char currentchar = character;
    switch (currentchar) {
    case '^':
        return 3;
        break;
    case '/':
        return 2;
        break;
    case '*':
        return 2;
        break;
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    default:
        return -1;
        break;
    }
} //function ends here

//function that returns a string which is postfix form of a infix
string InfixToPostfix(string expression) {
    string postfix = ""; //an empty string variable
    Stack <char> stack; //creating character type stack object
    //using enhanced for loop to iterate over the entered expression
    for (char characters : expression) {
        if (!isdigit(characters)) { //checking if character is not a digit
            if (characters == '(') { //if it is an opening bracket
                stack.push(characters); //push it into the stack
            }
            else if (characters == ')') { //if it is closing match bracket
                while (!stack.isEmpty() && stack.Peak() != '(') { //add the peak character to the expression till stack is not empty and new opening bracket is not detected
                    postfix += stack.Peak();
                    stack.pop(); //pop after each peak is added
                }
                stack.pop();
            }
            else if (characters == ' ') { //if a space is detected in case of more than one digit case
                postfix += characters; //add the space in the expression and continue the loop
                continue;
            }
            else {
                //updating the expression based on the precedence of top at the stack and current character in loop
                while (!stack.isEmpty() && precidence(characters) <= precidence(stack.Peak())) {
                    postfix += stack.Peak();
                    stack.pop();

                }
                stack.push(characters);

            }
        }
        else {
            //else a character is a digit as well, add  it into the expression
            postfix += characters;
        }

    }
    //while stack is not empty add the characters in top of the stack to the expression and pop it once 
    while (!stack.isEmpty()) {
        postfix += stack.Peak();
        stack.pop();
    }
    return postfix; //return the string expression
}//function ends here