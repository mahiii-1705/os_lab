		#include <stdio.h> int main() {	
		int n, bt[20], wt[20], tat[20], p[20];	
		int total_wt = 0, total_tat = 0; float avg_wt, avg_tat;

printf("Enter number of processes: ");	
		scanf("%d", &n);
printf("Enter burst time for each process:\n"); for (int i = 0; i < n; i++) {
printf("P%d: ", i + 1);
scanf("%d", &bt[i]); p[i] = i + 1;
}
// Sort according to burst time for (int i = 0; i < n - 1; i++) {
for (int j = i + 1; j < n; j++) { if (bt[i] > bt[j]) {
int temp = bt[i]; bt[i] = bt[j]; bt[j] = temp;
temp = p[i]; p[i] = p[j]; p[j] = temp;
}
}
}	
 

		wt[0] = 0; // first process has 0 waiting time for (int i = 1; i < n; i++)
wt[i] = wt[i - 1] + bt[i - 1];

for (int i = 0; i < n; i++) tat[i] = wt[i] + bt[i];

printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
for (int i = 0; i < n; i++) { printf("\nP%d\t\t%d\t\t%d\t\t%d", p[i], bt[i], wt[i], tat[i]); total_wt += wt[i];
total_tat += tat[i];
}	
			
		avg_wt = (float)total_wt / n;
avg_tat = (float)total_tat / n;
printf("\n\nAverage Waiting Time: %.2f", avg_wt); printf("\nAverage Turnaround Time: %.2f\n", avg_tat);	
		
return 0;
}
Round Robin #include <stdio.h>
int main() {
int n, bt[10], rem_bt[10], wt[10], tat[10]; int tq, time = 0, i;
float avg_wt = 0, avg_tat = 0;
printf("Enter number of processes: "); scanf("%d", &n);
printf("Enter burst time for each process:\n"); for (i = 0; i < n; i++) {
printf("P%d: ", i + 1);
scanf("%d", &bt[i]); rem_bt[i] = bt[i]; wt[i] = 0;
}	
 

		printf("Enter Time Quantum: "); scanf("%d", &tq);

int done; do {
done = 1;
for (i = 0; i < n; i++) { if (rem_bt[i] > 0) {
done = 0;
if (rem_bt[i] > tq) { time += tq; rem_bt[i] -= tq;
} else {
time += rem_bt[i]; wt[i] = time - bt[i];	
		rem_bt[i] = 0;	
		}
}
}
} while (!done);	
		for (i = 0; i < n; i++) { tat[i] = bt[i] + wt[i]; avg_wt += wt[i]; avg_tat += tat[i];
}

avg_wt /= n; avg_tat /= n;

printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
for (i = 0; i < n; i++) {
printf("\nP%d\t\t%d\t\t%d\t\t%d", i + 1, bt[i], wt[i], tat[i]);
}

printf("\n\nAverage Waiting Time: %.2f", avg_wt); printf("\nAverage Turnaround Time: %.2f\n", avg_tat);

return 0;
}	
