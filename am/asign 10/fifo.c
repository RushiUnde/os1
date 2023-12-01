#include <stdio.h>

int fifoPageFaults(int referenceString[], int n, int capacity) {
int fifoQueue[capacity]; 
int pageSet[capacity]; 
int pageFaults = 0;
int front = 0; 
int rear = -1; 
for (int i = 0; i < capacity; i++) {
fifoQueue[i] = -1; 
pageSet[i] = 0; 
}
for (int i = 0; i < n; i++) {
int page = referenceString[i];
int found = 0; 
for (int j = 0; j < capacity; j++) {
if (fifoQueue[j] == page) {
found = 1;
break;
}
}

if (!found) {
pageFaults++;

if (rear < capacity - 1) {
rear++;
} else {
rear = 0;
}
fifoQueue[rear] = page;
}
}
return pageFaults;
}
int main() {
int capacity;
int n; 
int referenceString[100]; 
printf("Enter the capacity of page frames: ");
scanf("%d", &capacity);

printf("Enter the number of page references: ");
scanf("%d", &n);

printf("Enter the reference string (space-separated, up to 100 elements):");
for (int i = 0; i < n; i++) {
scanf("%d", &referenceString[i]);
}

int pageFaults = fifoPageFaults(referenceString, n, capacity);

printf("Number of page faults using FIFO: %d\n", pageFaults);
return 0;
}

