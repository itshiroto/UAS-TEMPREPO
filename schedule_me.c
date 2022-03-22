#include<stdio.h>
#include<stdlib.h>

// Create a struct that would hold the data for a batch jobs
typedef struct {
    int id;
    int arrivalTime;
    int runTime;
    int turnAroundTime;
    int waitTime;
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

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            if (jobs[i].runTime > jobs[j].runTime) {
                job temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
            printf("%d ", jobs[i].id);
        }
    }
    printf("\n");
    // find turn around time
    for (int i = 0; i < 6; i++) {
        jobs[i].turnAroundTime = jobs[i].waitTime + jobs[i].runTime;
    }
    // find wait time
    jobs[0].waitTime = 0;
    for (int i = 1; i < 6; i++) {
        jobs[i].waitTime = jobs[i-1].waitTime + jobs[i-1].runTime;
    }
    
    // find total time it takes to run all jobs
    int totalTat = 0, totalWaitTime = 0, totalRuntime = 0;
    for (int i = 0; i < 6; i++) {
        totalTat += jobs[i].turnAroundTime;
        totalWaitTime += jobs[i].waitTime;
        totalRuntime += jobs[i].runTime;
    }
    int curr = 0;
    printf("%-10s %-10s\n", "Time", "Job ID");
    for(int i = 0; i <= totalRuntime; i++) {
        printf("%d - %d\n", i, jobs[curr].id);
    }
    float avgWaitTime = (float) totalWaitTime / 6;
    float avgTat = (float) totalTat / 6;
    printf("\nAverage Wait Time: %f\n", avgWaitTime);
    printf("Average Turn Around Time: %f\n", avgTat);

    return 0;
}