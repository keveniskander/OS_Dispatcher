/*
dispatcher.c

Student Name : Keven Iskander
Student ID # : 160634540

Dispatch Algorithm : Round Robin
*/

#include <string.h>
#include <stddef.h>
#include <stdio.h>

#include "queue.h"
#include "llist.h"

#define MAX_LINE_LENGTH 100



void dispatcher(FILE *fd, int quantum, int harddrive){
    /*
        Your code here.
        You may edit the following code
    */

	QNODE *new_front = NULL, *new_rear = NULL;
	QNODE *ready_front = NULL, *ready_rear = NULL;
	QNODE *blocked_front = NULL, *blocked_rear = NULL;
	QNODE *finished_front = NULL, *finished_rear = NULL;
	QNODE *running_front = NULL, *running_rear = NULL;
	NODE *exchange_list = NULL;

    char line_buffer[MAX_LINE_LENGTH];
    int start_time = 0, run_time = 0, process_id = 0, num_exchanges = 0, exchange_time;
    char *token;

    int total_blockedtime = 0, total_readytime = 0, total_runtime = 0, current_blockedtime = 0;
    int m = 0, n = 0;
    //Process simulation input line by line
    while (fgets(line_buffer, MAX_LINE_LENGTH, fd) != NULL && line_buffer[0] != '\n'){

        token = strtok(line_buffer, " ");
        sscanf(token, "%d",&start_time);

        token = strtok(NULL, " ");
        sscanf(token, "%d",&process_id);

        token = strtok(NULL, " ");
        sscanf(token, "%d",&run_time);

        num_exchanges = 0;
        token = strtok(NULL, " ");
        while ( token != NULL ){

            num_exchanges += sscanf(token, "%d",&exchange_time);
            token = strtok(NULL, " ");


            insert(&exchange_list, process_id, exchange_time);
        }
        enqueue(&new_front, &new_rear, process_id, start_time, run_time, total_runtime, total_readytime, total_blockedtime, current_blockedtime);
        m++;
       //printf("Process %3d wants to start at %6dms and run for %6dms and has %3d hard drive exchanges\n",  process_id, start_time, run_time, num_exchanges);

    }




	int time = 0;
	int process_zero_time = 0;
	int remaining = quantum + 100;





	while(m!=n){



		if(ready_front!= NULL && running_front == NULL){
			enqueue(&running_front, &running_rear, ready_front->process_id, ready_front->start_time, ready_front->run_time, ready_front->total_runtime, ready_front->total_readytime, ready_front->total_blockedtime, ready_front->current_blockedtime);
			dequeue(&ready_front, &ready_rear);

		}

		if(running_front!=NULL && running_front->run_time == 0){
			NODE *list3 = exchange_list;
			while(list3 != NULL){
				if(list3->data.process_id == running_front->process_id && list3->data.exchange == running_front->total_runtime){
					enqueue(&blocked_front, &blocked_rear, running_front->process_id, running_front->start_time, running_front->run_time, running_front->total_runtime, running_front->total_readytime, running_front->total_blockedtime, running_front->current_blockedtime);
					//dequeue(&running_front, &running_rear);
					//delete(&exchange_list, running_front->process_id, running_front->total_runtime);
					if(running_front!=NULL)dequeue(&running_front, &running_rear)
							;
					break;
				}
				list3 = list3->next;

			}
			if(running_front!=NULL){
				enqueue(&finished_front, &finished_rear, running_front->process_id, running_front->start_time, running_front->run_time, running_front->total_runtime, running_front->total_readytime, running_front->total_blockedtime, running_front->current_blockedtime);
				dequeue(&running_front, &running_rear);
				n++;
				remaining = quantum;

			}
		}

		if(new_front!=NULL && new_front->start_time== time){
			enqueue(&ready_front, &ready_rear, new_front->process_id, new_front->start_time, new_front->run_time, new_front->total_runtime, new_front->total_readytime, new_front->total_blockedtime, new_front->current_blockedtime);
			dequeue(&new_front, &new_rear);
			if(remaining==0){
				remaining = quantum;
			}
		}

		if(blocked_front != NULL && blocked_front->current_blockedtime == harddrive){

			if(blocked_front->run_time == 0){
				enqueue(&finished_front, &finished_rear, blocked_front->process_id, blocked_front->start_time, blocked_front->run_time, blocked_front->total_runtime, blocked_front->total_readytime, blocked_front->total_blockedtime, blocked_front->current_blockedtime);
				dequeue(&blocked_front, &blocked_rear);
				n++;
			}else{
				blocked_front->current_blockedtime = 0;
				enqueue(&ready_front, &ready_rear, blocked_front->process_id, blocked_front->start_time, blocked_front->run_time, blocked_front->total_runtime, blocked_front->total_readytime, blocked_front->total_blockedtime, blocked_front->current_blockedtime);
				dequeue(&blocked_front, &blocked_rear);
			}



			}

		if(running_front!=NULL && remaining !=0){

					NODE *list = exchange_list;
					    while(list != NULL){
					    	if(list->data.process_id == running_front->process_id && list->data.exchange == running_front->total_runtime){
					    		enqueue(&blocked_front, &blocked_rear, running_front->process_id, running_front->start_time, running_front->run_time, running_front->total_runtime, running_front->total_readytime, running_front->total_blockedtime, running_front->current_blockedtime);
					    		//dequeue(&running_front, &running_rear);
					    		//delete(&exchange_list, running_front->process_id, running_front->total_runtime);
					    		if(running_front!=NULL)dequeue(&running_front, &running_rear);
					    		break;
					    	}

					    	list = list->next;
					    }

					//if exchange time occurs while process is running
				}


		if(remaining == 0 && running_front != NULL ){
			NODE *list2 = exchange_list;
			while(list2!=NULL){
				if(list2->data.process_id == running_front->process_id && list2->data.exchange == running_front->total_runtime){
					enqueue(&blocked_front, &blocked_rear, running_front->process_id, running_front->start_time, running_front->run_time, running_front->total_runtime, running_front->total_readytime, running_front->total_blockedtime, running_front->current_blockedtime);
					if(running_front!=NULL)dequeue(&running_front, &running_rear);


					break;
				}

				list2 = list2->next;
			}if(running_front!=NULL){


				enqueue(&ready_front, &ready_rear, running_front->process_id, running_front->start_time, running_front->run_time, running_front->total_runtime, running_front->total_readytime, running_front->total_blockedtime, running_front->current_blockedtime);
				dequeue(&running_front, &running_rear);

			}
			remaining = quantum;
		}




		if(ready_front!= NULL && running_front == NULL){
			enqueue(&running_front, &running_rear, ready_front->process_id, ready_front->start_time, ready_front->run_time, ready_front->total_runtime, ready_front->total_readytime, ready_front->total_blockedtime, ready_front->current_blockedtime);
			dequeue(&ready_front, &ready_rear);



		}
		if(running_front == NULL && n!=m){
			process_zero_time += 1;
		}

		if(remaining==0){
				remaining = quantum;
			}

		QNODE *curr_blocked = blocked_front;
		while(curr_blocked!=NULL){
			curr_blocked->total_blockedtime += 1;
			curr_blocked = curr_blocked->next;
		}
		QNODE *fr_blocked = blocked_front;
		if(fr_blocked!=NULL){
			fr_blocked->current_blockedtime+=1;
		}


		QNODE *curr_ready = ready_front;
		while(curr_ready!=NULL){
			curr_ready->total_readytime += 1;
			curr_ready = curr_ready->next;
		}

		if(running_front!=NULL){
			running_front->run_time -= 1;
			//printf("%d ",running_front->run_time);
			running_front->total_runtime += 1;
		}




		//The following code was used to print every cycle for debugging purposes and was commented out


//		printf("time: %dms\n", time);
//		printf("processes in blocked queue: ");
//		QNODE *test_blocked = blocked_front;
//		while(test_blocked!=NULL){
//			printf("%d ", test_blocked->process_id);
//			test_blocked = test_blocked->next;
//		}
//		printf("\n");
//		printf("processes in new queue: ");
//		QNODE *test_new = new_front;
//		while(test_new!=NULL){
//			printf("%d ", test_new->process_id);
//			test_new = test_new->next;
//		}
//		printf("\n");
//		printf("processes in ready queue: ");
//		QNODE *test_ready = ready_front;
//				while(test_ready!=NULL){
//				printf("%d ", test_ready->process_id);
//				test_ready = test_ready->next;
//			}
//		printf("\n");
//		printf("processes in running queue: ");
//				QNODE *test_running = running_front;
//				while(test_running!=NULL){
//				printf("%d ", test_running->process_id);
//				test_running = test_running->next;
//			}
//		printf("\n");
//		printf("processes in finished queue: ");
//				QNODE *test_finished = finished_front;
//				while(test_finished!=NULL){
//				printf("%d ", test_finished->process_id);
//				test_finished = test_finished->next;
//			}
//		printf("\n");
//		printf("%d %d\n", quantum, remaining);
//		printf("--------------------------------------------------\n");



		remaining -=1;

		time += 1;

	}


	QNODE *print_finished = finished_front;
	printf(" 0 %d\n",process_zero_time);
	while(print_finished!=NULL){
		printf(" %d %d %d %d \n", print_finished->process_id, print_finished->total_runtime, print_finished->total_readytime, print_finished->total_blockedtime);
		print_finished = print_finished->next;
	}


}
