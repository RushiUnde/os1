#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int optimalPageFaults(int referenceString[], int n, int capacity) {
int pageFrames[capacity];
int futureUse[n];
int pageFaults = 0;
for (int i = 0; i < capacity; i++) {
pageFrames[i] = -1;
}
for (int i = 0; i < n; i++) {
futureUse[i] = n;
}
for (int i = 0; i < n; i++) {
int page = referenceString[i];
bool pageFound = false;
for (int j = 0; j < capacity; j++) {
if (pageFrames[j] == page) {
pageFound = true;
break;
}
}
if (!pageFound) {
pageFaults++;
int farthestIndex = -1;
for (int j = 0; j < capacity; j++) {
int future = futureUse[pageFrames[j]];
if (future > futureUse[farthestIndex]) {
farthestIndex = j;
}
}
pageFrames[farthestIndex] = page;
}
for (int j = i + 1; j < n; j++) {
if (referenceString[j] == page) {
futureUse[page] = j;
break;
}
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
int pageFaults = optimalPageFaults(referenceString, n, capacity);
printf("Number of page faults using Optimal (Belady's) algorithm: %d\n",pageFaults);
return 0;
}


