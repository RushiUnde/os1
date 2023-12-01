#include <stdio.h>
#include <stdlib.h>
int abs(int a) {
return a >= 0 ? a : -a;
}
void FCFS(int n, int head, int requests[]) {
int seekSequence = 0;
for (int i = 0; i < n; i++) {
seekSequence += abs(head - requests[i]);
head = requests[i];
}
printf("FCFS: Total seek time = %d\n", seekSequence);
}
void SCAN(int n, int head, int requests[], int direction) {
int seekSequence = 0;
int minCylinder = 0;
int maxCylinder = 200; // Adjust this value as per your system
for (int i = 0; i < n; i++) {
if (direction == 1 && requests[i] >= head) {
seekSequence += abs(head - requests[i]);
head = requests[i];
} else if (direction == -1 && requests[i] <= head) {
seekSequence += abs(head - requests[i]);
head = requests[i];
}
}
printf("SCAN: Total seek time = %d\n", seekSequence);
}
void CSCAN(int n, int head, int requests[]) {
int seekSequence = 0;
int minCylinder = 0;
int maxCylinder = 200; // Adjust this value as per your system
// Forward movement
seekSequence += (maxCylinder - head);
seekSequence += (maxCylinder - minCylinder);
head = minCylinder;
// Backward movement
for (int i = 0; i < n; i++) {
seekSequence += abs(head - requests[i]);
head = requests[i];
}
printf("C-SCAN: Total seek time = %d\n", seekSequence);
}
void SSTF(int n, int head, int requests[]) {
int seekSequence = 0;
int visited[n];
for (int i = 0; i < n; i++) {
visited[i] = 0;
}
for (int i = 0; i < n; i++) {
int minSeek = 1e9, pos = -1;
for (int j = 0; j < n; j++) {
if (!visited[j] && abs(head - requests[j]) < minSeek) {
pos = j;
minSeek = abs(head - requests[j]);
}
}
visited[pos] = 1;
seekSequence += minSeek;
head = requests[pos];
}
printf("SSTF: Total seek time = %d\n", seekSequence);
}
void LOOK(int n, int head, int requests[], int direction) {
int seekSequence = 0;
for (int i = 0; i < n; i++) {
int minSeek = 1e9, pos = -1;
for (int j = 0; j < n; j++) {
if (direction == 1 && requests[j] >= head && abs(head - requests[j]) < minSeek) {
pos = j;
minSeek = abs(head - requests[j]);
} else if (direction == -1 && requests[j] <= head && abs(head - requests[j]) < minSeek) {
pos = j;
minSeek = abs(head - requests[j]);
}
}
seekSequence += minSeek;
head = requests[pos];
}
printf("LOOK: Total seek time = %d\n", seekSequence);
}
void CLOOK(int n, int head, int requests[]) {
int seekSequence = 0;
int minCylinder = 0;
int maxCylinder = 200; // Adjust this value as per your system
// Forward movement
seekSequence += (maxCylinder - head);
// Backward movement
for (int i = 0; i < n; i++) {
seekSequence += abs(head - requests[i]);
head = requests[i];
}
printf("C-LOOK: Total seek time = %d\n", seekSequence);
}
int main() {
int n, head, direction;
printf("Enter the number of requests: ");
scanf("%d", &n);
printf("Enter the current head position: ");
scanf("%d", &head);
printf("Enter the request queue:\n");
int requests[n];
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
}
// Call each disk scheduling algorithm
FCFS(n, head, requests);
// Set the direction for SCAN and LOOK
printf("Enter the direction (1 for left, -1 for right): ");
scanf("%d", &direction);
SCAN(n, head, requests, direction);
CSCAN(n, head, requests);
SSTF(n, head, requests);
LOOK(n, head, requests, direction);
CLOOK(n, head, requests);
return 0;
}

