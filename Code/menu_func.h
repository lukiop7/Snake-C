/**
 * @file menu_func.h
 * @brief Contains menu function and functions that run the game
 * @author Lukasz Kwiecien
 */
#ifndef MENU_FUNC_H_INCLUDED
#define MENU_FUNC_H_INCLUDED

/** Function displays menu and calls other functions depending on user's choice.
 *
 *
 *
 */
void menu();

/** Main game function, calls other necessary functions.
 *
 *
 *
 */
void game();

/** Function displays a score and saves the nickname of the player when the game is over.
 *
 * \param head struct coordinate* Pointer to the first element of the list
 *
 *
 */
void dead(struct coordinate *  head);


/** Function sorts the top 20 results achieved by players and writes them down in a text file.
 *
 * \param name[] char
 * \param score int
 *
 *
 */
void sort_scores(char name[],int score);

/** Function displays top 20 results.
 *
 *
 */
void scores();

#endif
