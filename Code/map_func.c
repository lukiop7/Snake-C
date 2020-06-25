#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <windows.h>
#include <string.h>
#include<time.h>
#include "map_func.h"



void draw_borders(WINDOW *screen)
{
    int x, y, i;

    getmaxyx(screen, y, x);

    // 4 corners
    mvwprintw(screen, 0, 0, "+");
    mvwprintw(screen, y - 1, 0, "+");
    mvwprintw(screen, 0, x - 1, "+");
    mvwprintw(screen, y - 1, x - 1, "+");

    // sides
    for (i = 1; i < (y - 1); i++)
    {
        mvwprintw(screen, i, 0, "|");
        mvwprintw(screen, i, x - 1, "|");
    }

    // top and bottom
    for (i = 1; i < (x - 1); i++)
    {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
    }
}

void generate_food(WINDOW *win,struct coordinate *  head)
{
    if(food.y==head->y&&food.x==head->x) //checking if position of the head of snake is the same as food
    {
        food.hit=1;
        append(&head);
        head->length++;
        Beep(2500,50);

    }
    if(food.hit==1)
    {
        srand(time(0));
        food.x=rand()%78+1;
        food.y=rand()%22+1;
        if(food.x==head->x&&food.y==head->y) //generate random position
        {
            food.x=rand()%78+1;
            food.y=rand()%22+1;
        }
        mvwprintw(win,food.y, food.x, "*"); // Print our "food" at the current xy position
        wrefresh(win);
        food.hit=0;
        return;
    }
    if(food.hit==0&&food.y!=head->y||food.x!=head->x)
    {
        mvwprintw(win,food.y, food.x, "*"); // Print our "food" at the current xy position
        wrefresh(win);
    }

}
