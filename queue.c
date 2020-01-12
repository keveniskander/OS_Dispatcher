/*
--------------------------------------------------
Project: cp264a6q2
File:    queue.c
Author:  Keven Iskander
Professor: Hongbing Fan
Version: 2019-03-03
--------------------------------------------------
*/

#include "queue.h"

void enqueue(QNODE **frontp, QNODE **rearp, int val, int val2, int val3, int val4, int val5, int val6, int val7)
{
	QNODE *new = (QNODE*) malloc(sizeof(QNODE));

//	int z = 0;

//	while(val8[z] != '\0'){
//		new->exchange_array[z] = val8[z];
//		z++;
//	}

	new->process_id = val;
	new->start_time = val2;
	new->run_time = val3;
	new->total_runtime = val4;
	new->total_readytime = val5;
	new->total_blockedtime = val6;
	new->current_blockedtime = val7;
	new->next = NULL;
	if(*frontp == NULL && *rearp == NULL){
		*frontp = new;
		*rearp = *frontp;
	}else{
		(*rearp)->next = new;
		*rearp = new;
	}
}





int dequeue(QNODE **frontp, QNODE **rearp)
{
	QNODE *temp;
	int result = 0;
	if(*frontp != NULL){
		result = (*frontp)->process_id;
		if(*frontp == *rearp){
			*frontp = NULL;
			*rearp = NULL;
		}else{
			temp = *frontp;
			*frontp = (*frontp)->next;
			free(temp);
		}
	}
	return result;
}

int peek(QNODE *front)
{
	int val = 0;

	if(front != NULL){
		val = front->process_id;

	}else{
		//printf("Nothing to peek\n");
		val = 0;
	}
	return val;
}


int find_start(QNODE *front)
{
	int val = 0;

	if(front != NULL){
		val = front->start_time;

	}else{
		printf("No start time found\n");
		val = 0;
	}
	return val;
}
int find_runtime(QNODE *front)
{
	int val = 0;

	if(front != NULL){
		val = front->run_time;

	}else{
		printf("No run time found\n");
		val = 0;
	}
	return val;
}

void clean_queue(QNODE **frontp, QNODE **rearp)
{
	QNODE *p = *frontp, *temp;
	while(p != NULL){
		temp = p;
		p = p->next;
		free(temp);
	}
	*frontp = NULL;
	*rearp = NULL;
}
