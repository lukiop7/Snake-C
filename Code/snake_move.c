#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <windows.h>
#include <string.h>
#include<time.h>
#include "snake_move.h"

#define DELAY 60000

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR)
    {
        ungetch(ch);
        return 1;
    }
    else
    {
        return 0;
    }
}

void collision(struct coordinate * head)
{
    struct coordinate *last=head->next;
    while (last != NULL)
    {
        if(head->x==last->x&&head->y==last->y) //check if the position of the head of the snake is the same as position of one of elements of its body
        {
            head->lifes--;
            return;
        }
        last=last->next;
    }
}

void bend(struct coordinate **  head)
{
    struct coordinate *last=*head;
    while (last->next != NULL)
    {
        last=last->next;
    }
    while (last->prev != NULL) //assign position and direction of the previous element to the current element
    {
        last->x=last->prev->x;
        last->y=last->prev->y;
        last->direction=last->prev->direction;
        last = last->prev;
    }

}

void get_dir(struct coordinate *  head)
{
    int ch;
    if(kbhit())
    {
        ch=head->direction;
        head->direction=getch();
        if(head->direction==KEY_RIGHT)
        {
            if(ch==KEY_LEFT&&head->length!=1)  //if snake is longer than one blocks possibility to go backward
            {
                head->direction=ch;
                bend(&head);
                head->x--;
            }
            else
            {
                bend(&head);
                head->x++; // Advance the ball to the right
            }

        }

        if(head->direction==KEY_LEFT)
        {
            if(ch==KEY_RIGHT&&head->length!=1) //if snake is longer than one blocks possibility to go backward
            {
                head->direction=ch;
                bend(&head);
                head->x++;
            }
            else
            {
                bend(&head);
                head->x--;
            }

        }

        if(head->direction==KEY_UP)
        {
            if(ch==KEY_DOWN&&head->length!=1) //if snake is longer than one blocks possibility to go backward
            {
                head->direction=ch;
                bend(&head);
                head->y++;
            }
            else
            {
                bend(&head);
                head->y--; // Advance the ball to the right
            }

        }

        if(head->direction==KEY_DOWN)
        {
            if(ch==KEY_UP&&head->length!=1) //if snake is longer than one blocks possibility to go backward
            {
                head->direction=ch;
                bend(&head);
                head->y--;
            }
            else
            {
                bend(&head);
                head->y++;
            }

        }

    }
    else //direction stays the same
    {
        if(head->direction==KEY_RIGHT)
        {
            bend(&head);
            head->x++;
        }

        if(head->direction==KEY_LEFT)
        {
            bend(&head);
            head->x--;
        }

        if(head->direction==KEY_UP)
        {
            bend(&head);
            head->y--;
        }

        if(head->direction==KEY_DOWN)
        {
            bend(&head);
            head->y++;
        }
    }

}



void move_snake(WINDOW *win, WINDOW *field,struct coordinate *  head)
{

    if(head->x<1||head->x>78||head->y<1||head->y>23) //detect collision with wall
    {
        head->lifes--;
        head->x=1;
        head->y=1;
        head->direction=KEY_RIGHT;
        return;
    }
    struct coordinate *last=head;
    if(head->length==1) //print just head of the snake
    {

        mvwprintw(win,head->y, head->x, "o"); // Print our "snake" at the current xy position
        wrefresh(win);
        wrefresh(field);
        wclear(win);
        usleep(DELAY); // Shorter delay between movements

    }
    else
    {
        wclear(win);
        while (last!= NULL) //print entire body
        {
            mvwprintw(win,last->y, last->x, "o"); // Print our "snake" at the current xy position
            usleep(DELAY-((1000)*last->length));
            last=last->next;
        }


    }











}
