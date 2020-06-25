#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <windows.h>
#include <string.h>
#include<time.h>
#include "menu_func.h"
#include "snake_move.h"
#include "map_func.h"

#define DELAY 60000
void game()
{
    int parent_y,parent_x;
    initscr();// initialize Ncurses
    nodelay(stdscr, TRUE);
    keypad( stdscr, TRUE );//enable keyboard
    curs_set(FALSE);//hide cursor
    getmaxyx(stdscr, parent_y, parent_x);
    parent_x=(parent_x/2)-40;
    parent_y=(parent_y/2)-12;
    WINDOW *field = newwin(25, 80,parent_y, parent_x);// create a new field window
    WINDOW *border = newwin(25, 80,parent_y, parent_x);// create a new border window
    head=malloc(sizeof(struct coordinate)); //allocate memory for structure
    head->x=5;
    head->y=1;
    head->lifes=1;
    head->length=1;
    head->direction=KEY_RIGHT;
    head->next=NULL;
    head->prev=NULL;
    food.hit=1;//initial value 1 to generate food


    while(head->lifes!=0) //main loop of the game
    {
        draw_borders(border);
        collision(head);
        generate_food(border,head);
        get_dir(head);
        move_snake(border,field,head);

    }
    wclear(field);
    Beep(250,700); //sound effect
    clear();
    clear();
    endwin();
    endwin();
    dead(head);
}

void dead(struct coordinate *  head)
{
    FILE *f;
    f=fopen("scores.txt","a"); //create scores file
    fclose(f);
    char name[16];
    char temp[50];
    initscr();
    int parent_x,parent_y;
    getmaxyx(stdscr, parent_y, parent_x);
    nodelay(stdscr, TRUE);
    keypad( stdscr, TRUE );
    curs_set(TRUE);
    mvprintw(parent_y/2-2, parent_x/2 -10, "!!!YOU DIED!!!");
    mvprintw(parent_y/2-1, parent_x/2 -10, "  SCORE: %d",head->length-1);
    mvprintw(parent_y/2, parent_x/2 -10, "  NAME: ");
    mvprintw(parent_y/2+1, parent_x/2 -10, "(NICKNAME NO LONGER THAN 15 LETTERS)");
    mvprintw(parent_y/2+2, parent_x/2 -10, "USE _ INSTEAD OF SPACE ");
    mvscanw(parent_y/2,parent_x/2 -3,"%s",&temp);
    while(strlen(temp)>15) //checking if the length of the nickname is correct
    {
        clear();
        mvprintw(parent_y/2-2, parent_x/2 -10, "YOUR NICKNAME IS TOO LONG");
        mvprintw(parent_y/2-1, parent_x/2 -10, "  SCORE: %d",head->length-1);
        mvprintw(parent_y/2, parent_x/2 -10, "  NAME: ");
        mvscanw(parent_y/2,parent_x/2 -3,"%s",&temp);
    }
    if(strlen(temp)==0)
    {
        strcpy(temp,"unknown");
    }
    strcpy(name,temp);
    sort_scores(name,head->length-1);
    free_mem(&head);
    endwin();
    menu();
}

void sort_scores(char name[],int score)
{
    char names[20][30];
    int scores[20];
    int can=0;
    for( int i = 0; i < 20; i++ ) //filling array to avoid garbage values
    {
        strcpy(names[i],"N/A");
        scores[i]=999;
    }
    int cnt=-1; //counter -1 = no scores
    int temp;
    char* temp1[16];
    FILE *f;
    f=fopen("scores.txt","r+");
    while(!feof(f))
    {
        if(fscanf(f,"%d - %s \n",&scores[cnt+1],&names[cnt+1])==2) //reading scores and names from the file
        {
            cnt++;
        }
    }
    if(cnt<19) //top 20 is not full so we can add new one
    {
        scores[cnt+1]=score;
        strcpy(names[cnt+1],name);
    }
    else if(cnt==19) //top 20 is full, we have to check if the new score is bigger than the last
    {
        if(score>scores[19])
        {
            can=1;
        }
        if(can==1) //swapping last score with the new one
        {
            scores[19]=score;
            strcpy(names[19],name);
        }
    }

    for( int i = 0; i < 20; i++ ) //sorting using bubble sort
    {
        for( int j = 0; j < 20 - 1; j++ )
        {
            if( scores[ j ] > scores[ j + 1 ] )
            {
                temp=scores[j];
                strcpy(temp1,names[j]);
                strcpy(names[j],names[j+1]);
                strcpy(names[j+1],temp1);
                scores[j]=scores[j+1];
                scores[j+1]=temp;
            }

        }
    }
    if(cnt<19) //because initial value of counter is -1 we have to add 1
    {
        cnt+=1;
    }
    rewind(f);
    for( int i = cnt; i >=0; i-- ) //writing sorted results to the file
    {
        fprintf(f,"%d - %s \n",scores[i],names[i]);
    }
    fclose(f);
}


void scores()
{
    initscr(); // initialize Ncurses
    noecho();
    int parent_x,parent_y;
    getmaxyx(stdscr, parent_y, parent_x);
    parent_y=parent_y/2 -13;
    parent_x=parent_x/2 -18;
    nodelay(stdscr, TRUE);
    keypad( stdscr, TRUE );
    curs_set(FALSE);
    start_color(); //2
    init_pair( 1, COLOR_YELLOW, COLOR_BLACK ); //colors
    init_pair( 2, COLOR_RED, COLOR_BLACK );
    init_pair( 3, COLOR_MAGENTA, COLOR_BLACK );
    char name [20][16];
    int score[20];
    int cnt=0;
    int ch;
    FILE *f;
    f=fopen("scores.txt","a+"); //a+ = if scores file doesn't exist - create
    while(!feof(f)) //reading results from the file
    {
        if(fscanf(f,"%d - %s \n",&score[cnt],&name[cnt])==2)
        {
            cnt++;
        }


    }
    cnt-=1;
    for(int i=19; i>=0; i--)
    {
        if(i==cnt||i<cnt) //scores file is not empty
        {
            if(i==2)
            {
                attron( COLOR_PAIR( 3 ) );
                mvprintw(parent_y+i+2,parent_x,"%d.%-20s - %d",i+1,name[i],score[i]);
                refresh();
                usleep(DELAY+250000);
            }
            if(i==1)
            {
                attron( COLOR_PAIR( 2 ) );
                mvprintw(parent_y+i+2,parent_x,"%d.%-20s - %d",i+1,name[i],score[i]);
                refresh();
                usleep(DELAY+250000);
            }
            if(i==0)
            {
                attron( COLOR_PAIR( 1 ) );
                mvprintw(parent_y+i+2,parent_x,"%d.%-20s - %d",i+1,name[i],score[i]);
                refresh();
                usleep(DELAY+250000);
            }
            else
            {
                mvprintw(parent_y+i+2,parent_x,"%d.%-20s - %d",i+1,name[i],score[i]);
                refresh();
                usleep(DELAY+250000);
            }
        }
        else //no score - print N/A
        {
            mvprintw(parent_y+i+2,parent_x,"%d.N/A",i+1);
            refresh();
            usleep(DELAY+250000);
        }

    }
    fclose(f);
    ch=getch();
    while(ch!=10) //wait for enter to come back to menu
    {
        ch=getch();
    }
    clear();
    refresh();
    endwin();
    menu();
}

void menu()
{
    int parent_y,parent_x;
    WINDOW *w;
    initscr(); // initialize Ncurses
    getmaxyx(stdscr, parent_y, parent_x);
    w = newwin( 5, 12, (parent_y/2)-5, (parent_x/2) -7); // create a new window
    box( w, 0, 0 ); //create box
    keypad(w,TRUE);
    curs_set(FALSE);
    char choices[3][8]= {"START","TOP 20","EXIT"};
    char item [8];
    int choice;
    int highligth=0;
    while(1) //keeps menu displayed if no key is pressed
    {
        for(int i=0; i<3; i++) //highlighting current choice
        {
            if(i==highligth)
            {
                wattron(w,A_STANDOUT);
            }
            sprintf(item, "%s",  choices[i]);
            mvwprintw(w,i+1,1,"%s",item);
            wattroff(w,A_STANDOUT);
        }
        wrefresh(w);
        choice=wgetch(w);
        switch(choice) //changing highlighted element depending on arrow keys
        {
        case KEY_UP:
            highligth--;
            if(highligth==-1)
                highligth=0;
            break;
        case KEY_DOWN:
            highligth++;
            if(highligth==3)
                highligth=2;
            break;
        default:
            break;
        }
        if(choice==10)
            break;
    }
    switch(highligth) //go to chosen function
    {
    case 0:
        endwin();
        game();

        break;
    case 1:
        wclear(w);
        wrefresh(w);
        endwin();
        scores();
        break;
    case 2:
        return 0;
    default:
        break;
    }
    endwin();
}


