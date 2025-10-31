#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void read_matrix(int n, int m, int mat[n][m], const char *name) {
    printf("Enter %s matrix (%d rows, %d columns), row by row:\n", name, n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (scanf("%d", &mat[i][j]) != 1) {
                fprintf(stderr, "Input error reading %s[%d][%d]\n", name, i, j);
                exit(EXIT_FAILURE);
            }
            if (mat[i][j] < 0) {
                fprintf(stderr, "Negative values not allowed; found %d\n", mat[i][j]);
                exit(EXIT_FAILURE);
            }
        }
    }
}


void read_vector(int m, int vec[m], const char *name) {
    printf("Enter %s vector (%d values):\n", name, m);
    for (int j = 0; j < m; ++j) {
        if (scanf("%d", &vec[j]) != 1) {
            fprintf(stderr, "Input error reading %s[%d]\n", name, j);
            exit(EXIT_FAILURE);
        }
        if (vec[j] < 0) {
            fprintf(stderr, "Negative values not allowed; found %d\n", vec[j]);
            exit(EXIT_FAILURE);
        }
    }
}

void compute_need(int n, int m, int need[n][m], int max[n][m], int alloc[n][m]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            need[i][j] = max[i][j] - alloc[i][j];
            if (need[i][j] < 0) {
                fprintf(stderr, "Error: Allocation > Max for process %d resource %d\n", i, j);
                exit(EXIT_FAILURE);
            }
        }
    }
}

bool bankers_safety(int n, int m, int alloc[n][m], int need[n][m], int available[m], int safe_seq_out[n]) {
    int work[m];
    bool finish[n];

    for (int j = 0; j < m; ++j) work[j] = available[j];
    for (int i = 0; i < n; ++i) finish[i] = false;

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool can_allocate = true;
                // Check if Need[i] <= Work
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    // Work = Work + Allocation[i]
                    for (int j = 0; j < m; ++j) work[j] += alloc[i][j];
                    safe_seq_out[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break; // no further process can proceed
    }

    if (count == n) return true;
    return false;
}

int deadlock_detection(int n, int m, int alloc[n][m], int request[n][m], int available[m], int deadlocked_out[n]) {
    int work[m];
    bool finish[n];
    bool progress = true;

    for (int j = 0; j < m; ++j) work[j] = available[j];
    for (int i = 0; i < n; ++i) {
        bool all_zero = true;
        for (int j = 0; j < m; ++j) {
            if (alloc[i][j] != 0) {
                all_zero = false;
                break;
            }
        }
        finish[i] = all_zero ? true : false;
    }

    do {
        progress = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool can_satisfy = true;
                // Check if Request[i] <= Work
                for (int j = 0; j < m; ++j) {
                    if (request[i][j] > work[j]) {
                        can_satisfy = false;
                        break;
                    }
                }

                if (can_satisfy) {
                    // 3. Process can finish; release its allocation
                    // Work = Work + Allocation[i]
                    for (int j = 0; j < m; ++j) work[j] += alloc[i][j];
                    finish[i] = true;
                    progress = true;
                }
            }
        }
    } while (progress);

    // 4. Check for deadlocked processes
    int dead_count = 0;
    for (int i = 0; i < n; ++i) {
        if (!finish[i]) {
            deadlocked_out[dead_count++] = i;
        }
    }
    return dead_count;
}

int main() {
    int n, m; // n: number of processes, m: number of resource types

    printf("Number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of processes\n");
        return 1;
    }
    printf("Number of resource types: ");
    if (scanf("%d", &m) != 1 || m <= 0) {
        fprintf(stderr, "Invalid number of resource types\n");
        return 1;
    }

    int alloc[n][m];
    int max[n][m];
    int need[n][m];
    int available[m];
    int safe_seq[n];
    int deadlocked[n];

    read_matrix(n, m, alloc, "Allocation");
    read_matrix(n, m, max, "Max");
    read_vector(m, available, "Available");

    compute_need(n, m, need, max, alloc);

    printf("\nComputed Need matrix:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) printf("%3d ", need[i][j]);
        printf("\n");
    }

    bool safe = bankers_safety(n, m, alloc, need, available, safe_seq);

    if (safe) {
        printf("\nSystem is in a SAFE state. \\nSafe sequence: ");
        for (int i = 0; i < n; ++i) {
            printf("P%d", safe_seq[i]);
            if (i < n - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in a safe state (UNSAFE).\n");
    }

    int dead_count = deadlock_detection(n, m, alloc, need, available, deadlocked);

    printf("\nDeadlock Detection: ");
    if (dead_count == 0) {
        printf("No deadlocked processes detected.\n");
    } else {
        printf("%d deadlocked process(es): ", dead_count);
        for (int k = 0; k < dead_count; ++k) {
            printf("P%d", deadlocked[k]);
            if (k < dead_count - 1) printf(", ");
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}