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

//function that returns a double after the expression passed in the argument is evaluated
double evaluate(string expression) {
    int i; //variable to be used in loop
    Stack <double> values(expression.length()); //stack object double type that stores numeric values
    Stack <char> ops(expression.length());//  //stack object character type that stores operators
    //for loop iterates over whole expression
    for ( i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') //if a space is detected, then continue
            continue;
        //if the character is an opening bracket push it into operators stack
        else if (expression[i] == '(') {
            ops.push(expression[i]);
        }
        //if the character is a digit
        else if (isdigit(expression[i])) {
            double val = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                val = (val * 10) + (expression[i] - double('0'));
                i++;
            }
            //push the existing value into values stack
            values.push(val);
            i--;
        }

        // if closing bracket is detected, perform the operation using operation function
        else if (expression[i] == ')')
        {
            while (!ops.isEmpty() && ops.Peak() != '(')
            {
                double val2 = values.Peak();
                values.pop();
                double val1 = values.Peak();
                values.pop();
                char op = ops.Peak();
                ops.pop();
                values.push(operation(val1, val2, op));
            }

            // pop opening brace till stacket is empty
            if (!ops.isEmpty())
                ops.pop();
        }
        // Current character is an operator.
        else
        {
            // While operator stack is not empty and its top possess equal or greater precedence to current operator
            //perform the operation between two consecutive values at the top of value stack
            while (!ops.isEmpty() && precidence(ops.Peak())
                >= precidence(expression[i])) {
                double val2 = values.Peak();
                values.pop();
                double val1 = values.Peak();
                values.pop();
                char op = ops.Peak();
                ops.pop();
                values.push(operation(val1, val2, op));
            }

            // Push current character operator to operator stacks.
            ops.push(expression[i]);
        }
    }

    // This while loop applies operation between the two consecutive values at the top of the of the values stack
    while (!ops.isEmpty()) {
        double val2 = values.Peak();
        values.pop();
        double val1 = values.Peak();
        values.pop();
        char op = ops.Peak();
        ops.pop();
        values.push(operation(val1, val2, op));
    }
    return values.Peak(); //at last returns the finalize value at the top of values stack
} //function ends here


//creating main function
int main() {
    cout << "Enter an infix expression to be converted to postfix \n";
    cout<< "(Expression must have a space if two digit or more number is entered)\n";
    string expression; //variable that stores user entered expression
    cout << "Infix Expression: ";
    getline(cin, expression); //using getline to take user input expression so that spaces are read
    if (validityCheck(expression))//checks if the expression is valid (as in balanced braces)
    {
        cout << "\nPostfix expression: " << InfixToPostfix(expression); //displaying the converted expression using concerned function
        cout << "\nValue of expression = " << evaluate(expression); //displaying the value of expression using concerned function
    }
    else { //else displaying that expression is invalid
        cout << "\nThe entered infix expression is invalid";
    }
    return 0;
} //main ends here
