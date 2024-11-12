#include <stdio.h>
#include <string.h>

typedef struct {
    char sign[15];
    char lane[15];
} Activity;

typedef struct {
    Activity activity;
    int seconds;
    int priority;
} Lane;

typedef struct {
    Lane arr[8];
    int count;
} PriorityQueue;


int main() {


    buildmaxHeap(&pq);
    maxHeapSort(&pq);
    displayPQ(pq);

    
    char scenarios[3][2][15] = {
        {"straight", "main"},
        {"left", "main"},
        {"right", "main"}
    };
    int num_scenarios = 3;

    processMultipleScenarios(pq, scenarios, num_scenarios);

    return 0;
}

int getTime(PriorityQueue pq, char* start_sign, char* start_lane, char* end_sign, char* end_lane) {
    int startInd, sum = 0;
    for (int i = 0; i < pq.count; i++) {
        if (strcmp(start_sign, pq.arr[i].activity.sign) == 0 && strcmp(start_lane, pq.arr[i].activity.lane) == 0) {
            startInd = i;
            break;
        }
    }

    
    for (int i = startInd + 1; i < pq.count; i++) {
        sum += pq.arr[i].seconds;
        if (strcmp(end_sign, pq.arr[i].activity.sign) == 0 && strcmp(end_lane, pq.arr[i].activity.lane) == 0) {
            break;
        }
    }

    return sum;
}

void processMultipleScenarios(PriorityQueue pq, char scenarios[][2][15], int num_scenarios) {
    FILE *fp = fopen("traffic_result.dat", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(fp, "Scenario Results:\n");
    printf("\nScenario Results:\n");

    for (int i = 0; i < num_scenarios; i++) {
        int result = getTime(pq, scenarios[i][0], scenarios[i][1], "pedestrian", "main");

        fprintf(fp, "Scenario %d: Time from %s %s to pedestrian main = %d seconds\n",
                i + 1, scenarios[i][0], scenarios[i][1], result);
        printf("Scenario %d: Time from %s %s to pedestrian main = %d seconds\n",
               i + 1, scenarios[i][0], scenarios[i][1], result);
    }

    fclose(fp);
}
