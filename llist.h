/*
--------------------------------------------------
Project: cp264a5q1
File:    llist.h
Author:  Keven Iskander
Professor: Hongbing Fan
Version: 2019-02-15
--------------------------------------------------
*/

#ifndef LLIST
#define LLIST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**  this is from a5q1
 * RECORD structure
 * name  - char array for person's name
 * score - float score of record
 */
typedef struct  {
  int process_id;
  int exchange;
} RECORD;

/**
 * linked list node structure
 * data  - RECORD data
 * next  - pointer pointing to next node of linked list
 */
typedef struct node1 {
	RECORD data;
	struct node1 *next;

} NODE;

/**
 * Display linked list.
 * @param start Pointer to the first node of linked list.
 */
void display(NODE *start);

/**
 * Search linked list for name key.
 * @param start Pointer to the first node of linked list.
 * @param name Key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE *search(NODE *start, int process_id, int exchange_time);

/**
 * Insert new record to linked list at the sorted position.
 * @param startp Pointer pointing to the start pointer of linked list, used to update the start node address in case of change.
 * @param name The name data of new record.
 * @param score The score data of new record
 */
void insert(NODE **startp, int process_id, int exchange_time);

//==================================================
int delete(NODE **startp,  int process_id, int exchange_time);

//==================================================
//void clean(NODE **startp);


// The following functions are adapted from previous assignments
//==================================================
void import_data(NODE **startp, char *filename);

//==================================================
void report_data(NODE *start,  char *filename);

//==================================================
char letter_grade(float score);

//==================================================
void swap(float *first, float *second );

//==================================================
void quick_sort(float *a, int m, int n);

//==================================================
float median(NODE *start);

#endif
