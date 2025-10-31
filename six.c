//1) First In First Out-
#include <stdio.h>

int main() {
    int pages[30], frames[10], n, f, i, j, k, pageFaults = 0, next = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);	
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage Replacement Process (FIFO):\n");

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }

        if (!found) {
            frames[next] = pages[i];
            next = (next + 1) % f;
            pageFaults++;
        }

        printf("Step %2d: ", i + 1);
        for (k = 0; k < f; k++) {
            if (frames[k] != -1)
                printf("%d ", frames[k]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (FIFO): %d\n", pageFaults);
    return 0;
}

//2) Least Replacement Used(LRU)-
#include <stdio.h>

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++)
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    return pos;
}

int main() {
    int pages[30], frames[10], time[10], counter = 0;
    int n, f, i, j, pos, pageFaults = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage Replacement Process (LRU):\n");

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }

        if (!found) {
            int empty = -1;
            for (j = 0; j < f; j++)
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }

            if (empty != -1)
                pos = empty;
            else
                pos = findLRU(time, f);

            frames[pos] = pages[i];
            time[pos] = ++counter;
            pageFaults++;
        }

        printf("Step %2d: ", i + 1);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (LRU): %d\n", pageFaults);
    return 0;
}

//3) Optimal-
#include <stdio.h>

int predict(int pages[], int frames[], int n, int index, int f) {
    int farthest = index, res = -1;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }
    return (res == -1) ? 0 : res;
}

int main() {
    int pages[30], frames[10], n, f, i, j, pos, pageFaults = 0;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter reference string: ");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage Replacement Process (Optimal):\n");

    for (i = 0; i < n; i++) {
        int found = 0;
        for (j = 0; j < f; j++)
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }

        if (!found) {
            int empty = -1;
            for (j = 0; j < f; j++)
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }

            if (empty != -1)
                pos = empty;
            else
                pos = predict(pages, frames, n, i + 1, f);

            frames[pos] = pages[i];
            pageFaults++;
        }

        printf("Step %2d: ", i + 1);
        for (j = 0; j < f; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n");
    }

    printf("\nTotal Page Faults (Optimal): %d\n", pageFaults);
    return 0;
}