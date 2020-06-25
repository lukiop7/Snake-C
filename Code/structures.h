/**
 * @file structures.h
 * @brief Contains doubly linked list and its functions and structure that holds data on food
 * @author Lukasz Kwiecien
 */
#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

/** doubly-linked list for storing informations about the snake */
struct coordinate
{
    int x; /**< x position */
    int y;/**< y position */
    int lifes;/**<number of lifes */
    int direction;/**< directon of movement */
    int length;/**< length of the snake */
    struct coordinate *next;/**< pointer to the next element of the list */
    struct coordinate *prev;/**< pointer to the previous element of the list */
};
struct coordinate *head;

/** structure that holds data on food*/
struct food_
{
    int x;/**< x position */
    int y;/**<  y position */
    int hit;/**<  variable for checking if food has been eaten*/
};
struct food_ food;


/** Function adds new element at the end of the doubly linked list.
 *
 * \param head struct coordinate** Pointer to a pointer to the first element of the list
 *
 *
 */
void append(struct coordinate** head);

/** Function removes all elements of the list.
 *
 * \param head struct coordinate** Pointer to a pointer to the first element of the list
 *
 *
 */
void free_mem(struct coordinate **  head);

#endif
