#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <windows.h>
#include <string.h>
#include <time.h>


void append(struct coordinate** head)
{
    /* 1. allocate node */
    struct coordinate* e = (struct coordinate*) malloc(sizeof(struct coordinate));

    struct coordinate *last = *head;  /* used in step 5*/

    /* 2. put in the data  */
    e->direction=(*head)->direction;
    e->lifes=(*head)->lifes;
    if((*head)->direction==KEY_RIGHT)
    {
        e->x=((*head)->x)-1;
        e->y=(*head)->y;
    }

    if((*head)->direction==KEY_LEFT)
    {
        e->x=((*head)->x)+1;
        e->y=(*head)->y;
    }
    if((*head)->direction==KEY_UP)
    {
        e->x=(*head)->x;
        e->y=((*head)->y)+1;
    }
    if((*head)->direction==KEY_DOWN)
    {
        e->x=(*head)->x;
        e->y=((*head)->y)-1;
    }
    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    e->next = NULL;

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = e;
    e->prev = last;
    return;
}

void free_mem(struct coordinate **  head)
{
    struct coordinate *last=*head;
    while (last->next != NULL)
    {
        last=last->next;
    }
    while (last->prev != NULL)
    {
        last = last->prev;
        free(last->next);
    }
    free(head);


}

