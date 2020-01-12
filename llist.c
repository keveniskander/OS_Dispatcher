/*
--------------------------------------------------
Project: cp264a5q1
File:    llist.c
Author:  Keven Iskander
Professor: Hongbing Fan
Version: 2019-02-15
--------------------------------------------------
*/

#include "llist.h"

#include <stdio.h>
#include <stdlib.h>


//void display(NODE *start) {
//	printf("Value Address\n");
//	  while(start != NULL) {
//	    printf("%5d %d\n", start->data.process_id, start);
//	    start = start->next;
//	  }
//}

NODE* search(NODE *startp, int process_id, int exchange_time) {
	while((startp != NULL) && (startp->data.process_id != process_id )) {
	    startp = startp->next;
	  }
	  return startp;
}

//from dllist
void insert(NODE **startp, int process_id, int exchange_time) {
	struct node1* np = (struct node1 *)malloc(sizeof(struct node1));
		  if (np == NULL) {printf("malloc fails"); return;}
		  np->data.process_id = process_id;
		  np->data.exchange = exchange_time;
		  np->next = NULL;

		  np->next = *startp;
		  *startp = np;
}

int delete(NODE **startp, int process_id, int exchange_time) {
	struct node1 *np = *startp;
		  struct node1 *prev = NULL;

		  while ( (np != NULL) && (np->data.process_id != process_id && np->data.exchange != exchange_time)) {
		    prev = np;
		    np = np->next;
		  }

		  if (np == NULL)
		    return 0;
		  else {
		    if (prev == NULL)
		      *startp = np->next;
		    else
		      prev->next = np->next;

		#ifdef usefree
		    free(np);
		#endif

		    return 1;
		  }
}

//from dllist
//void delete_start(NODE **startp) {
//  NODE *ptr = *startp;
//  if ( ptr != NULL) {
//    if (ptr->next == NULL) {
//       *startp = NULL;
//    }
//    else {
//      *startp = ptr->next;
//    }
//    free(ptr);
//  }
//}

//void clean(NODE **startp) {
//	struct node *temp, *np = *startp;
//	  while (np != NULL) {
//	    temp = np;
//	    np = np -> next;
//	    free(temp);
//	  }
//	  *startp = NULL;
//}
