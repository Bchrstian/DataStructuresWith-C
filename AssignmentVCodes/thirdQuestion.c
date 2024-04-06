#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

typedef struct {
    char arr[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

void push(Stack *s, char c) {
    if (!isFull(s)) {
        s->arr[++s->top] = c;
    }
}

char pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[s->top--];
    }
    return '\0';
}

char peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->arr[s->top];
    }
    return '\0';
}

int isMatchingPair(char opening, char closing) {
    // Simplified the function logic
    return (opening == '(' && closing == ')') ||
           (opening == '{' && closing == '}') ||
           (opening == '[' && closing == ']');
}

int checkBalancedBrackets(FILE *file) {
    Stack s;
    char c;
    initStack(&s);

    while ((c = fgetc(file)) != EOF) {
        if (c == '(' || c == '{' || c == '[') {
            push(&s, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(&s) || !isMatchingPair(pop(&s), c)) {
                return 0;
            }
        }
    }

    return isEmpty(&s);
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    if (checkBalancedBrackets(file)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    fclose(file);
    return 0;
}
