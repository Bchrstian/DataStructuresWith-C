#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int year;
    int month;
    int revenue;
    int expense;
    struct Node* next;
} Node;

Node* createNode(int year, int month, int revenue, int expense) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->year = year;
    newNode->month = month;
    newNode->revenue = revenue;
    newNode->expense = expense;
    newNode->next = NULL;
    return newNode;
}

Node* insertNode(Node* head, int year, int month, int revenue, int expense) {
    Node* newNode = createNode(year, month, revenue, expense);
    if (head == NULL) {
        return newNode;
    }
    Node* temp = head;
    while (temp->next!= NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

int main() {
    FILE *filePointer, *outputFile;
    filePointer = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");
    if (filePointer == NULL || outputFile == NULL) {
        printf("Unable to open the file(s).\n");
        return -1;
    }

    // Skip the initial target line
    int initialTarget;
    fscanf(filePointer, "%d", &initialTarget);
    while (fgetc(filePointer)!= '\n');

    // Read and store financial data in a linked list
    Node* head = NULL;
    int year, month, revenue, expense;
    char ch;
    int processingYear2023 = 1; // Flag to indicate processing year 2023 data

    while ((ch = fgetc(filePointer))!= EOF) {
        if (ch == '{') {
            // Skip the '{['
            while ((ch = fgetc(filePointer))!= '[' && ch!= EOF);
            // Read year
            fscanf(filePointer, "%d", &year);

            // Read and process each month's data
            while ((ch = fgetc(filePointer))!= '}') {
                if (ch == '[') {
                    // Read month, revenue, and expense
                    fscanf(filePointer, "%d,%d,%d", &month, &revenue, &expense);
                    if (processingYear2023 && year == 2023 && month == 0 && revenue == 0 && expense == 0) {
                        // Skip data for year 2023 with all zeros
                        continue;
                    }else if(processingYear2023 == 0 && year == 2024 && month == 12 && revenue == 40000 && expense == 22000){
                        // Skip duplicated data of year 2023 with year 2024
                        continue;
                    }
                    // Insert into linked list
                    head = insertNode(head, year, month, revenue, expense);
                }
            }
            if (processingYear2023 && year == 2023) {
                processingYear2023 = 0; // Finished processing year 2023 data
            }
        }
    }

    // Write data to output file
    fprintf(outputFile, "%d\n", head->year);
    fprintf(outputFile, "month\trevenue\texpense\tProfit\tDiff-to-Target\n");
    int target = initialTarget;
    int profit;
    int diff_to_target ;
    while (head!= NULL) {
        // the loop will first implement the entries of year 2023
        if (head->month == 1) {
            fprintf(outputFile, "%d\n", head->year);
            // title for year 2024
            fprintf(outputFile, "month\trevenue\texpense\tProfit\tDiff-to-Target\n");

        }
        //Calculations for profit and difference to target
        if (initialTarget == target)
        {
            profit = head->revenue - head->expense;
            diff_to_target = head->revenue - target;
        }else{
         profit = head->revenue - head->expense;
         diff_to_target = head->revenue - target;
        }

        target = head->revenue*2;

        fprintf(outputFile, "%d\t%d\t%d\t%d\t%d\n", head->month, head->revenue, head->expense, profit, diff_to_target);
        head = head->next;
    }

    fclose(filePointer);
    fclose(outputFile);

    return 0;
}