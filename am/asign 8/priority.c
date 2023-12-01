#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int finish_time;
};

// Function to perform Priority Scheduling
void priorityScheduling(struct Process processes[], int n) {
    // Sort processes based on priority (ascending order)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                // Swap processes
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate finish times, waiting times, and turnaround times
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].finish_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].finish_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        current_time = processes[i].finish_time;
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
    }

    // Perform Priority Scheduling
    priorityScheduling(processes, n);

    // Display results
    printf("\nProcess\tBurst Time\tPriority\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time,
               processes[i].priority, processes[i].finish_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    return 0;
}

