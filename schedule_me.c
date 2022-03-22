#include<stdio.h>
#include<stdlib.h>

// Create a struct that would hold the data for a batch jobs
typedef struct {
    int id;
    int arrivalTime;
    int runTime;
} job;

int main() {
    job jobs[6];
    int id[6] = {1, 2, 3, 4, 5, 6};
    int arrivalTime[6] = {0, 2, 3, 5, 7, 8};
    int runTime[6] = {10, 6, 3, 4, 7, 1};
    for (int i = 0; i < 6; i++) {
        jobs[i].id = id[i];
        jobs[i].arrivalTime = arrivalTime[i];
        jobs[i].runTime = runTime[i];
    }

    // Simulate the batch job scheduling using SJF algorithm
    // based on already existed jobs array and assuming all arrivalTme are sorted
    // And prints the process using format "time - executed job id"
    int time = 0;
    int i = 0;
    while (i < 6) {
        if (jobs[i].arrivalTime <= time) {
            printf("%d - %d\n", time, jobs[i].id);
            time += jobs[i].runTime;
            i++;
        } else {
            time++;
        }
    }
    return 0;
}