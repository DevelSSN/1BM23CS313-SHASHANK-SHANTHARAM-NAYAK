// Online C compiler to run C program online
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int top=-1, size=25;

int prec(char c){
	return (c=='^')?3:(c=='/'||c=='*')?2:(c=='+'||c=='-')?1:-1;
}

bool isEmpty(){return (top==-1);}
bool isFull(){return (top==size-1);}

bool isRtoL(char op){return (op=='^');}

char Top(char s[]){if (!isEmpty()) {
        return s[top];
    }
    return '\0';  }
void push(char s[], char x)
{
	if (!isFull()) {
        ++top;
        s[top] = x;
    }
}

char pop(char s[]){
	if (!isEmpty()) {
        return s[top--];
    }
    return '\0'; 
}

void in2post(){
    char req[25];
    char s[25];  // Stack for operators
    char res[25];  // Result array
    int resIndex = 0;

    printf("Enter expression: ");
    fgets(req, sizeof(req), stdin);

    int len = strlen(req);
    memset(res, 0, sizeof(res));  // Clear result array

    for (int i = 0; i < len; i++) {
        char c = req[i];

        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            res[resIndex++] = c;  // Append operand to result
        } else if (c == '(') {
            push(s, c);  // Push '(' to stack
        } else if (c == ')') {
            while (!isEmpty() && Top(s) != '(') {
                res[resIndex++] = pop(s);
            }
            pop(s);  // Pop '(' from stack
        } else if (prec(c) > prec(Top(s))) {
            push(s, c);  // Push operator to stack
        } else {
            while (!isEmpty() && ((prec(c) < prec(Top(s))) || (prec(c) == prec(Top(s)) && !isRtoL(c)))) {
                res[resIndex++] = pop(s);
            }
            push(s, c);
        }
    }

    // Clear stack
    while (!isEmpty()) {
        res[resIndex++] = pop(s);
    }

    res[resIndex] = '\0';  // Null-terminate the result string
    printf("Result: %s\n", res);
}

void main()
{
	in2post();
}
