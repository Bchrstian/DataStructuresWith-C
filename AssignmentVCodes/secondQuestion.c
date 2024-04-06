#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for customer requests
struct CustomerRequest {
    char telNumber[50];
    char names[50];
    char requestSummary[50];
};

// Define a linked list node for customer requests
struct RequestNode {
    struct CustomerRequest data;
    struct RequestNode* next;
};

// Function to create a new node
struct RequestNode* createNode(struct CustomerRequest request) {
    struct RequestNode* newNode = (struct RequestNode*)malloc(sizeof(struct RequestNode));
    newNode->data = request;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new request at the end of the queue
void enqueue(struct RequestNode** head, struct CustomerRequest request) {
    struct RequestNode* newNode = createNode(request);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct RequestNode* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to remove the first request from the queue
void dequeue(struct RequestNode** head) {
    if (*head == NULL) {
        printf("Queue is empty.\n");
        return;
    }
    struct RequestNode* temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Function to write a request to the output file
void writeRequestToFile(struct CustomerRequest request) {
    FILE* outputFile = fopen("output1.txt", "a");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return;
    }
    fprintf(outputFile, "PhoneNumber: %s\t   Full Names: %s\tRequestSummary: %s\n", request.telNumber, request.names, request.requestSummary);
    fclose(outputFile);
}

void takeinput(char c[50])
{
    fgets(c, 50, stdin);
    c[strlen(c) - 1] = 0;
}

int main() {
    struct RequestNode* queue = NULL;
    struct CustomerRequest forFile;

    printf("Enter Customer PhoneNumber: ");
    takeinput(forFile.telNumber);

    printf("Enter Customer Name: ");
    takeinput(forFile.names);

    printf("Enter Customer RequestSummary: ");
    takeinput(forFile.requestSummary);
    
    fgetc(stdin); // Clear the newline character from the buffer

    enqueue(&queue, forFile);

    // Dequeue the first request (customer attended)
    dequeue(&queue);

    // Write the attended request to the output file
    writeRequestToFile(forFile);

    // Free memory
    while (queue != NULL) {
        struct RequestNode* temp = queue;
        queue = queue->next;
        free(temp);
    }

    return 0;
}
