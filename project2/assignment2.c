#include "assignment1.h"
#include "assignment2.h"
#include "workload.h"
#include "scheduler.h"
#include "governor.h"

// Note: Deadline of each workload is defined in the "workloadDeadlines" variable.
// i.e., You can access the dealine of the BUTTON thread using workloadDeadlines[BUTTON]
// See also deadlines.c and workload.h

// Assignment: You need to implement the following two functions.

// learn_workloads(SharedVariable* v):
// This function is called at the start part of the program before actual scheduling
// - Parameters
// sv: The variable which is shared for every function over all threads
void learn_workloads(SharedVariable* sv) {
	// TODO: Fill the body
	// This function is executed before the scheduling simulation.
	// You need to calculate the execution time of each thread here.

	// Thread functions for workloads: 
	// thread_button, thread_twocolor, thread_temp, thread_track,
	// thread_shock, thread_rgbcolor, thread_aled, thread_buzzer

	// Tip 1. You can call each workload function here like:
	// thread_button();

	// Tip 2. You can get the current time here like:
	// long long curTime = get_current_time_us();
}


// select_task(SharedVariable* sv, const int* aliveTasks):
// This function is called while runnning the actual scheduler
// - Parameters
// sv: The variable which is shared for every function over all threads
// aliveTasks: an array where each element indicates whether the corresponed task is alive(1) or not(0).
// idleTime: a time duration in microsecond. You can know how much time was waiting without any workload
//           (i.e., it's larger than 0 only when all threads are finished and not reache the next preiod.)
// - Return value
// TaskSelection structure which indicates the scheduled task and the CPU frequency
TaskSelection select_task(SharedVariable* sv, const int* aliveTasks, long long idleTime) {

	static int prev_selection = -1;
	static int selection = 0;
    int alive_tasks = 7;
    long long curTime = get_scheduler_elapsed_time_us();
    long long min = sv->last_run[prev_selection]+workloadDeadlines[prev_selection];

    int j=0;
    long long curr;
    for (j=0;j<8;j++){
        curr = sv->last_run[j]+workloadDeadlines[j];
        // printDBG("min:%lld - task %d: %lld - alive:%d \n", min, j, curr, aliveTasks[j]); 
        if ( curr < min) {
            if (aliveTasks[j] == 1){
                selection = j;
                min = sv->last_run[j]+workloadDeadlines[j];
            }
            else{
                alive_tasks--;
            }
        }
    }

	// The retun value can be specified like this:
    prev_selection = selection;
	TaskSelection sel;
	sel.task = selection; // The thread ID which will be scheduled. i.e., 0(BUTTON) ~ 7(BUZZER)
	sel.freq = 1; // Request the maximum frequency (if you want the minimum frequency, use 0 instead.)
    // printDBG("%lld - Scheduling task:%d - High:%d - Last run:%lld - Deadline %lld\n",curTime, sel.task, 
    //        sel.freq, sv->last_run[sel.task], workloadDeadlines[sel.task]);
    // printDBG("%d", sel.task);
    sv->last_run[sel.task] = sv->last_run[sel.task]+workloadDeadlines[sel.task];

    return sel;

	// Sample scheduler: Round robin
	/* It selects a next thread using aliveTasks.
	int i = prev_selection + 1;
	while(1) {
		if (i == NUM_TASKS)
			i = 0;

		if (aliveTasks[i] == 1) {
			prev_selection = i;
			break;
		}
		++i;
	}*/
}
