#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_REQUESTS 100

void simulate_fcfs(int requests[], int num_requests, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;

    printf("\n--- FCFS Disk Scheduling Simulation ---\n");
    printf("Head Movement Path: %d", current_head);

    for (int i = 0; i < num_requests; i++) {
        int seek_distance = abs(requests[i] - current_head);
        total_seek_time += seek_distance;
        current_head = requests[i];
        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (FCFS): %d tracks\n", total_seek_time);
    printf("---------------------------------------\n");
}
void simulate_sstf(int requests[], int num_requests, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;
    int served[MAX_REQUESTS] = {0};
    int served_count = 0;

    printf("\n--- SSTF Disk Scheduling Simulation ---\n");
    printf("Head Movement Path: %d", current_head);

    while (served_count < num_requests) {
        int min_seek_distance = INT_MAX;
        int next_index = -1;
        for (int i = 0; i < num_requests; i++) {
            if (served[i] == 0) {
                int seek_distance = abs(requests[i] - current_head);
                if (seek_distance < min_seek_distance) {
                    min_seek_distance = seek_distance;
                    next_index = i;
                }
            }
        }

        total_seek_time += min_seek_distance;
        current_head = requests[next_index];
        served[next_index] = 1;
        served_count++;

        printf(" -> %d", current_head);
    }

    printf("\nTotal Head Movement (SSTF): %d tracks\n", total_seek_time);
    printf("---------------------------------------\n");
}
int main() {
    int num_requests, initial_head;
    int requests[MAX_REQUESTS];

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    printf("Enter the request sequence: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);

    simulate_fcfs(requests, num_requests, initial_head);
    simulate_sstf(requests, num_requests, initial_head);

    return 0;
}