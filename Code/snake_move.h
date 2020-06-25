/**
 * @file snake_move.h
 * @brief Functions related to action of moving a snake.
 * @author Lukasz Kwiecien
 */
#ifndef SNAKE_MOVE_H_INCLUDED
#define SNAKE_MOVE_H_INCLUDED
#include "structures.h"

/** Function determines if a key has been pressed or not.
 *
 * \param void
 * \return int returns 1 if key was pressed otherwise returns 0
 *
 */
int kbhit(void);

/** Function sets a position and direction of movement of the head of the snake, depending on the pressed key.
 *
 * \param head struct coordinate* Pointer to the first element of the list
 *
 *
 */
void get_dir(struct coordinate *  head);

/** Function sets a correct direction of movement and position(x,y) for each element of a snake.
 *
 * \param head struct coordinate** Pointer to a pointer to the first element of the list
 *
 *
 */
void bend(struct coordinate **  head);

/** Function prints all elements of a snake's body in the appropriate positions.
 *
 * \param win WINDOW* Pointer to the window(ncurses).
 * \param field WINDOW* Pointer to the window(ncurses).
 * \param head struct coordinate* Pointer to the first element of the list
 *
 *
 */
void move_snake(WINDOW *win, WINDOW *field,struct coordinate *  head);

/** Function detects collision between head of a snake and its body.
 *
 * \param head struct coordinate* Pointer to the first element of the list
 *
 *
 */
void collision(struct coordinate * head);


#endif
