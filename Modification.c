#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"

#define MODIFY_MENU_POINT "Choose the modification:\n\t1. X coordinate\n\t2. Y coordinate\n\t0. Exit\nChoice : "
#define MODIFY_MENU_STYLE "Choose the modification:\n\t1. the color\n\t2. the color border\n\t3. the translate\n\t4. the rotate\n\t0. Exit\nChoice : "
#define MODIFY_MENU_OVAL "Choose the modification:\n\t1. the new coordinate (X,Y)\n\t2. the new styles\n\t3. the new radius height\n\t4. the new radius width\n\t0. Exit\nChoice : "
#define MODIFY_MENU_RECTANGLE "Choose the modification:\n\t1. the new coordinate (X,Y)\n\t2. the new styles\n\t3. the new length\n\t4. the new width\n\t0. Exit\nChoice : "
#define MODIFY_MENU_LINE "Choose the modification:\n\t1. the new coordinate of point A (X,Y)\n\t2. the new coordinate of point B (X,Y)\n\t3. the new style\n\t0. Exit\nChoice : "

/**
 * @brief Modifies the properties of a Point structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * X and Y coordinates of the Point. The user can choose to modify each
 * coordinate or exit the modification process.
 *
 * @param point Pointer to the Point structure to be modified.
 */
void modify_point(Point *point)
{
    int choice;
    do
    {
        choice = ask_for_int(MODIFY_MENU_POINT);
        switch (choice)
        {
        case 1:
            point->x = ask_for_float("Select the X coordinate : ");
            break;
        case 2:
            point->y = ask_for_float("Select the Y coordinate : ");
            break;
        }
    } while (choice != 0);
}

/**
 * @brief Modifies the properties of a Style structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * color, border color, translation, and rotation of the Style. The user can
 * choose to modify each property or exit the modification process.
 *
 * @param style Pointer to the Style structure to be modified.
 */
void modify_style(Style *style)
{
    int choice;
    do
    {
        choice = ask_for_int(MODIFY_MENU_STYLE);
        switch (choice)
        {
        case 1:
            style->color = ask_for_char("Select the background color : ");
            break;
        case 2:
            style->color_border = ask_for_char("Select the border color : ");
            break;
        case 3:
            style->translate = ask_for_float("Select the new translation : ");
            break;
        case 4:
            style->rotate = ask_for_float("Select the new rotation : ");
            break;
        }
    } while (choice != 0);
}

/**
 * @brief Modifies the properties of an Ovale structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * coordinates of point A, the style, radius height, and radius width of the Ovale.
 * The user can choose to modify each property or exit the modification process.
 *
 * @param oval Pointer to the Ovale structure to be modified.
 */
void modify_oval(Oval *oval)
{
    int choice;
    do
    {
        choice = ask_for_int(MODIFY_MENU_OVAL);
        switch (choice)
        {
        case 1:
            modify_point(oval->A);
            break;
        case 2:
            modify_style(oval->S);
            break;
        case 3:
            oval->height_radius = ask_for_float("Select the radius height : ");
            break;
        case 4:
            oval->width_radius = ask_for_float("Select the radius width : ");
            break;
        }
    } while (choice != 0);
}

/**
 * @brief Modifies the properties of a Rectangle structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * coordinates of point A, the style, length, and width of the Rectangle. The user
 * can choose to modify each property or exit the modification process.
 *
 * @param rectangle Pointer to the Rectangle structure to be modified.
 */
void modify_rectangle(Rectangle *rectangle)
{
    int choice;
    do
    {
        choice = ask_for_int(MODIFY_MENU_RECTANGLE);
        switch (choice)
        {
        case 1:
            modify_point(rectangle->A);
            break;
        case 2:
            modify_style(rectangle->S);
            break;
        case 3:
            rectangle->length = ask_for_float("Select the new length : ");
            break;
        case 4:
            rectangle->width = ask_for_float("Select the new width : ");
            break;
        }
    } while (choice != 0);
}

/**
 * @brief Modifies the properties of a Ligne structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * coordinates of points A and B, as well as the style of the Ligne. The user
 * can choose to modify each property or exit the modification process.
 *
 * @param line Pointer to the Ligne structure to be modified.
 */
void modify_line(Line *line)
{
    int choice;
    do
    {
        choice = ask_for_int(MODIFY_MENU_LINE);
        switch (choice)
        {
        case 1:
            modify_point(line->A);
            break;
        case 2:
            modify_point(line->B);
            break;
        case 3:
            modify_style(line->S);
            break;
        }
    } while (choice != 0);
}
