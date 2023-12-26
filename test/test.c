#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Define a stack structure
typedef struct {
    int top;
    double* items;
} Stack;

// Function to initialize a stack
void initialize(Stack* stack, int size) {
    stack->top = -1;
    stack->items = (double*)malloc(size * sizeof(double));
}

// Function to push an item onto the stack
void push(Stack* stack, double item) {
    stack->items[++stack->top] = item;
}

// Function to pop an item from the stack
double pop(Stack* stack) {
    return stack->items[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to get the precedence of an operator
int getPrecedence(char operator) {
    if (operator == '+' || operator == '-')
        return 1;
    else if (operator == '*' || operator == '/')
        return 2;
    else if (operator == '^')
        return 3;
    return 0;
}

// Function to convert infix expression to postfix notation
void infixToPostfix(char* infix, char* postfix) {
    Stack operatorStack;
    initialize(&operatorStack, strlen(infix));
    int i, j;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i]) || infix[i] == '.' || (infix[i] == '-' && (i == 0 || !isdigit(infix[i - 1])))) {
            // If the current character is a digit or a decimal point, add it to the postfix expression
            postfix[j++] = infix[i];
        } else if (infix[i] == 'E') {
            // Handle 'E' as 10 to the power of
            postfix[j++] = 'E';
        } else if (infix[i] == '(') {
            // If the current character is an opening parenthesis, push it onto the stack
            push(&operatorStack, infix[i]);
        } else if (infix[i] == ')') {
            // If the current character is a closing parenthesis, pop operators from the stack
            // and add them to the postfix expression until an opening parenthesis is encountered
            while (!isEmpty(&operatorStack) && operatorStack.items[operatorStack.top] != '(') {
                postfix[j++] = pop(&operatorStack);
            }
            // Pop the opening parenthesis from the stack
            pop(&operatorStack);
        } else {
            // If the current character is an operator, pop operators from the stack
            // and add them to the postfix expression until a lower precedence operator or an opening parenthesis is encountered
            while (!isEmpty(&operatorStack) && getPrecedence(operatorStack.items[operatorStack.top]) >= getPrecedence(infix[i])) {
                postfix[j++] = pop(&operatorStack);
            }
            // Push the current operator onto the stack
            push(&operatorStack, infix[i]);
        }
    }

    // Pop any remaining operators from the stack and add them to the postfix expression
    while (!isEmpty(&operatorStack)) {
        postfix[j++] = pop(&operatorStack);
    }

    // Null-terminate the postfix expression
    postfix[j] = '\0';
}

// Function to evaluate a postfix expression
double evaluatePostfix(char* postfix) {
    Stack operandStack;
    initialize(&operandStack, strlen(postfix));
    int i;

    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i]) || postfix[i] == '.' || (postfix[i] == '-' && (i == 0 || !isdigit(postfix[i - 1])))) {
            // If the current character is a digit or a decimal point, convert the substring to a double and push it onto the stack
            char* endptr;
            double operand = strtod(&postfix[i], &endptr);
            push(&operandStack, operand);
            // Move the index to the end of the number
            i = endptr - postfix - 1;
        } else if (postfix[i] == 'E') {
            // If the current character is 'E', pop the top operand from the stack and replace it with 10 to the power of that operand
            double operand = pop(&operandStack);
            push(&operandStack, pow(10, operand));
        } else {
            // If the current character is an operator, pop the top two operands from the stack, perform the operation, and push the result onto the stack
            double operand2 = pop(&operandStack);
            double operand1 = pop(&operandStack);
            switch (postfix[i]) {
                case '+':
                    push(&operandStack, operand1 + operand2);
                    break;
                case '-':
                    push(&operandStack, operand1 - operand2);
                    break;
                case '*':
                    push(&operandStack, operand1 * operand2);
                    break;
                case '/':
                    push(&operandStack, operand1 / operand2);
                    break;
                case '^':
                    push(&operandStack, pow(operand1, operand2));
                    break;
            }
        }
    }

    // The final result should be on top of the stack
    return pop(&operandStack);
}

int main() {
    char infixExpression[] = "1.234E3.4*1+2/4-5^3+2*(5+1)";
    char postfixExpression[strlen(infixExpression) * 2];  // Maximum possible length of postfix expression
    infixToPostfix(infixExpression, postfixExpression);
    double result = evaluatePostfix(postfixExpression);

    printf("Infix Expression: %s\n", infixExpression);
    printf("Postfix Expression: %s\n", postfixExpression);
    printf("Result: %lf\n", result);

    return 0;
}
