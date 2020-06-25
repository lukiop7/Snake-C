/**
 * @file map_func.h
 * @brief Functions to create a map and generate food
 * @author Lukasz Kwiecien
 */
#ifndef MAP_FUNC_H_INCLUDED
#define MAP_FUNC_H_INCLUDED
#include "structures.h"

/** Function draws a map in a given window.
 *
 * \param screen WINDOW* Pointer to the window(ncurses).
 *
 *
 */
void draw_borders(WINDOW *screen);

/** Function generates and prints food in a random position.
 *
 * \param win WINDOW* Pointer to a window(ncurses).
 * \param head struct coordinate* Pointer to the first element of the list
 *
 *
 */
void generate_food(WINDOW *win,struct coordinate *  head);

#endif
