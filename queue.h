/*
--------------------------------------------------
Project: cp264a6q2
File:    queue.h
Author:  Keven Iskander
Professor: Hongbing Fan
Version: 2019-03-03
--------------------------------------------------
*/

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <malloc.h>

typedef struct node {
  int process_id;
  int start_time;
  int run_time;
  int total_runtime;
  int total_readytime;
  int total_blockedtime;
  int current_blockedtime;
  struct node *next;
} QNODE;


void enqueue(QNODE **frontp, QNODE **rearp, int, int, int, int, int, int, int);
int dequeue(QNODE **frontp, QNODE **rearp);
int peek(QNODE *front);
int find_start(QNODE *front);
int find_runtime(QNODE *front);
void clean_queue(QNODE **frontp, QNODE **rearp);

#endif
