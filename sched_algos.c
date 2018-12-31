/*Afreen Hameed CS332 Project1: Operating System Scheduling Algorithms
Includes: 
FIRST IN FIRST OUT
PROIRITY
SHORTEST PROCESS NEXT
SHORTEST REMAINING TIME
ROUND ROBIN

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sched_algos.h"

//function declarations

void quickSort(struct process ** processes, int start, int end); //sort priority in descending order
int wall (struct process ** processes, int start, int end) ;
void quickSort1(struct process ** processes, int start, int end);//sort duartion in ascending order
int wall1 (struct process ** processes, int start, int end) ;
void exchange(struct process ** p1, struct process ** p2) ; //helper to quicksorts
void CopyArray(struct process ** from,struct process ** to,int arrSize); //copies elements between to and from


void fillProcessArr(struct process ** processArr, int arrSize) { //Helper function to fill our array with randomly generated processes.
  int currIdx = 0;
  while(currIdx < arrSize) {
    processArr[currIdx] = malloc(sizeof(struct process));
    processArr[currIdx]->id = currIdx + 1;
    processArr[currIdx]->duration = rand() % 5 + 1;
    //my code
    processArr[currIdx]->priority=rand()%5 + 1;
    //end of my code
    currIdx++;
  }
}

void outputProcess(struct process *process) { //Helper function to output a single process.
    printf("Process ID: %i, Duration: %i, Priority=%d\n", process->id, process->duration,process->priority);
}

void outputProcesses(struct process ** processes, int arrSize) {
  int idx = 0;
  while(idx < arrSize) { 
    outputProcess(processes[idx]);
    idx++;
  }
}

int main(int argc, char ** argv) {
  srand(time(NULL)); //Seed our random with the current time.
  const int ARR_SIZE = 10; //The size of our array of randomly generated processes.
  const int TIME_SLICE = 2; //The time slice for any preemptive scheduling algorithms.
  struct process ** processes = malloc(sizeof(struct process *) * ARR_SIZE); //Our process array, used in each of our scheduling algorithms.
  int ** priorities = malloc(sizeof(int *) * ARR_SIZE); //Our priorities array, used for priority scheduling. Index i of the priorities array corresponds to the same index of the processes array.

  fillProcessArr(processes, ARR_SIZE);
  //fillPrioritiesArr(priorities, ARR_SIZE); HINT: you will need to fill up the priorities array similarly to how the processes one is filled.
  
  printf("Outputting initial process array:\n");
  outputProcesses(processes, ARR_SIZE);
  printf("\n\n");
  
  //Each of the bestart function calls should NOT change the original processes array. For sorting, you must create a copy of the original array within the function.

  sched_fcfs(processes, ARR_SIZE);
  sched_priority(processes, ARR_SIZE, priorities);
  sched_spn(processes, ARR_SIZE);
  sched_srt(processes, ARR_SIZE, TIME_SLICE);
  sched_round_robin(processes, ARR_SIZE, TIME_SLICE);

  //Final heap cleanup should go here - deallocate all objects on the original array, including the space allocated for the array itself. This goes for the priorities array as well.
  free(processes);
  free(priorities);
}

void sched_fcfs(struct process ** processes, int arrSize) {
  printf("First Come First Serve:\n");
  outputProcesses(processes,arrSize); //same as initial array
  printf("\n\n");
}

void sched_priority(struct process ** processes, int arrSize, int ** priorities) {
  printf("Priority:\n");
  struct process ** schedp_processes=malloc(sizeof(struct process *) * arrSize);

  if(schedp_processes!=NULL){
    CopyArray(processes,schedp_processes,arrSize);

    quickSort( schedp_processes, 0, arrSize-1); //sort according to priority
    outputProcesses(schedp_processes,arrSize);
  }
  free(schedp_processes);
  printf("\n\n");
}

void sched_spn(struct process ** processes, int arrSize) {
  printf("Shortest Process Next:\n");
  struct process ** schedp_processes=malloc(sizeof(struct process *) * arrSize);

  if(schedp_processes!=NULL){
    CopyArray(processes,schedp_processes,arrSize);
    quickSort1( schedp_processes, 0, arrSize-1); //sort according to duration
    outputProcess(schedp_processes[0]);
    outputProcess(schedp_processes[1]);
    schedp_processes[0]->id = 11;
    schedp_processes[0]->duration = rand() % 5 + 1;
    schedp_processes[0]->priority=rand()%5 + 1;
    schedp_processes[1]->id = 12;
    schedp_processes[1]->duration = rand() % 5 + 1;
    schedp_processes[1]->priority=rand()%5 + 1;
    quickSort1( schedp_processes, 0, arrSize-1); //sort according to duration
    outputProcesses(schedp_processes,arrSize);
  }
  free(schedp_processes);
  printf("\n\n");
}

void sched_srt(struct process ** processes, int arrSize, int timeSlice) {
  printf("Shortest Remaining Time:\n");
  struct process ** schedp_processes=malloc(sizeof(struct process *) * arrSize);

  if(schedp_processes!=NULL){
    CopyArray(processes,schedp_processes,arrSize);
    int currIdx=0;
    quickSort1( schedp_processes, 0, arrSize-1);
    int check=1;
    while(currIdx<arrSize){
          while(schedp_processes[currIdx]->duration>0){ //can do this since currIdx always shortest
            schedp_processes[currIdx]->duration-=timeSlice;
            if(schedp_processes[currIdx]->duration<0) schedp_processes[currIdx]->duration=0;//fixing negation
            if(currIdx==3 && check==1){
                  schedp_processes[0]->id = 11;
                  schedp_processes[0]->duration = rand() % 5 + 1;
                  schedp_processes[0]->priority=rand()%5 + 1;
                  schedp_processes[1]->id = 12;
                  schedp_processes[1]->duration = rand() % 5 + 1;
                  schedp_processes[1]->priority=rand()%5 + 1;
                  quickSort1( schedp_processes, 0, arrSize-1); //sort according to duration
                  check=0;
                  currIdx=currIdx-2;
            }
            outputProcess(schedp_processes[currIdx]);
          }
          currIdx++;
    }
  }
  free(schedp_processes);
  printf("\n\n");
}

void sched_round_robin(struct process ** processes, int arrSize, int timeSlice) {
  printf("Round Robin:\n");
  struct process ** schedp_processes=malloc(sizeof(struct process *) * arrSize);

  if(schedp_processes!=NULL){
    CopyArray(processes,schedp_processes,arrSize);
    int currIdx=0;
    int count=0;//num of processes complete
    while(count<arrSize){ 

          if(schedp_processes[currIdx]->duration==0){ //skip 
            currIdx=(currIdx+1)%arrSize; //circular array
            continue;
          }
          schedp_processes[currIdx]->duration-=timeSlice;  //process        
          if(schedp_processes[currIdx]->duration<=0){ //process complete
            schedp_processes[currIdx]->duration=0;
            count++;  
          }
      outputProcess(schedp_processes[currIdx]);
      currIdx=(currIdx+1)%arrSize;

    }
  }
  free(schedp_processes);
  printf("\n\n");
}


//Copier
void CopyArray(struct process ** from,struct process ** to,int arrSize){
  for(int i=0; i < arrSize; i++){
      to[i] = malloc(sizeof(struct process));

      to[i]->id=from[i]->id;
      to[i]->duration=from[i]->duration;
      to[i]->priority=from[i]->priority;
      
  }

}


void exchange(struct process ** p1, struct process ** p2) { 
    struct process * temp = *p1; 
    *p1 = *p2; 
    *p2 = temp; 
} 
  
int wall (struct process ** processes, int start, int end) { 
    struct process * pivotp = processes[end];    
    int i = (start - 1);  
  
    for (int n = start; n <= end- 1; n++) 
    {  
        if (processes[n]->priority >= pivotp->priority) 
        { 
            i++;
            exchange(&processes[i], &processes[n]); 
        } 
    } 
    exchange(&processes[i + 1], &processes[end]); 
    return (i + 1); 
} 

void quickSort(struct process ** processes, int start, int end) { 
    if (start < end) 
    { 
        int divider = wall(processes, start, end); 
 
        quickSort(processes, start, divider - 1); 
        quickSort(processes, divider + 1, end); 
    } 
} 

int wall1 (struct process ** processes, int start, int end) { 
    struct process * pivotp = processes[end];    
    int i = (start - 1);  
  
    for (int n = start; n <= end- 1; n++) 
    {  
        if (processes[n]->duration <= pivotp->duration) 
        { 
            i++;
            exchange(&processes[i], &processes[n]); 
        } 
    } 
    exchange(&processes[i + 1], &processes[end]); 
    return (i + 1); 
} 

void quickSort1(struct process ** processes, int start, int end) { 
    if (start < end) 
    { 
        int divider = wall1(processes, start, end); 
 
        quickSort1(processes, start, divider - 1); 
        quickSort1(processes, divider + 1, end); 
    } 
} 
