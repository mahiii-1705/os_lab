#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

int memory[MAX_BLOCKS];

void initialize() {
    for (int i = 0; i < MAX_BLOCKS; i++)
        memory[i] = 0;
}

void sequential_allocation() {
    int start = 5;   
    int length = 4;  

    printf("\n--- Sequential File Allocation ---\n");
    printf("File start block = %d, length = %d\n", start, length);

    if (start + length > MAX_BLOCKS) {
        printf("File exceeds memory limit.\n");
        return;
    }

    for (int i = start; i < (start + length); i++) {
        if (memory[i] == 1) {
            printf("Block %d already allocated.\n", i);
            return;
        }
    }

    for (int i = start; i < (start + length); i++)
        memory[i] = 1;

    printf("File allocated from block %d to %d\n", start, start + length - 1);
}

void indexed_allocation() {
    int indexBlock = 12;       
    int blocks[] = {20, 21, 22};  
    int n = sizeof(blocks) / sizeof(blocks[0]);

    printf("\n--- Indexed File Allocation ---\n");
    printf("Index block = %d\n", indexBlock);

    if (memory[indexBlock] == 1) {
        printf("Index block already allocated.\n");
        return;
    }

    memory[indexBlock] = 1;

    for (int i = 0; i < n; i++) {
        if (memory[blocks[i]] == 0)
            memory[blocks[i]] = 1;
        else
            printf("Block %d already allocated.\n", blocks[i]);
    }

    printf("File indexed at block %d allocated to blocks: ", indexBlock);
    for (int i = 0; i < n; i++)
        printf("%d ", blocks[i]);
    printf("\n");
}

void linked_allocation() {
    int blocks[] = {30, 31, 32};  
    int n = sizeof(blocks) / sizeof(blocks[0]);

    printf("\n--- Linked File Allocation ---\n");
    printf("File blocks: ");
    for (int i = 0; i < n; i++)
        printf("%d ", blocks[i]);
    printf("\n");

    for (int i = 0; i < n; i++) {
        if (memory[blocks[i]] == 0)
            memory[blocks[i]] = 1;
        else {
            printf("Block %d already allocated.\n", blocks[i]);
            return;
        }
    }

    for (int i = 0; i < n - 1; i++)
        printf("Block %d → %d allocated.\n", blocks[i], blocks[i + 1]);

    printf("File stored using linked allocation.\n");
}

int main() {
    initialize();

    printf("===== FILE ALLOCATION STRATEGIES SIMULATION =====\n");
    sequential_allocation();
    indexed_allocation();
    linked_allocation();

    printf("\nAll allocations completed successfully.\n");
    return 0;
}