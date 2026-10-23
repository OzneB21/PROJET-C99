#include <stdio.h>
#include <stdlib.h>
#include "shapes.h"
#include <errno.h>

/**
 * @brief Modifies the properties of a Point structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * X and Y coordinates of the Point. The user can choose to modify each
 * coordinate or exit the modification process.
 *
 * @param point Pointer to the Point structure to be modified.
 */
Oval *create_oval(float height_radius, float width_radius, Point *A, Style *S)
{
    Oval *oval = malloc(sizeof(Oval));
    if (oval == NULL)
        return NULL;
    oval->A = A;
    oval->S = S;
    oval->height_radius = height_radius;
    oval->width_radius = width_radius;
    return oval;
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
Rectangle *create_rectangle(float width, float length, Point *A, Style *S)
{
    Rectangle *rectangle = malloc(sizeof(Rectangle));
    if (rectangle == NULL)
        return NULL;
    rectangle->A = A;
    rectangle->S = S;
    rectangle->width = width;
    rectangle->length = length;
    return rectangle;
}

/**
 * @brief Modifies the properties of a Line structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * coordinates of points A and B, as well as the style of the Line. The user
 * can choose to modify each property or exit the modification process.
 *
 * @param line Pointer to the Line structure to be modified.
 */
Line *create_line(Point *A, Point *B, Style *S)
{
    Line *line = malloc(sizeof(Line));
    if (line == NULL)
        return NULL;
    line->A = A;
    line->B = B;
    line->S = S;
    return line;
}

/**
 * @brief Creates a new Point structure with the specified coordinates.
 *
 * This function allocates memory for a new Point structure and initializes
 * its X and Y coordinates with the provided values.
 *
 * @param x The X coordinate of the point.
 * @param y The Y coordinate of the point.
 * @return A pointer to the newly created Point structure, or NULL if memory allocation fails.
 */
Point *create_point(float x, float y)
{
    Point *point = malloc(sizeof(Point));
    if (point == NULL)
        return NULL;
    point->x = x;
    point->y = y;
    return point;
}

/**
 * @brief Creates a new Style structure with the specified properties.
 *
 * This function allocates memory for a new Style structure and initializes
 * its color, border color, translation, and rotation with the provided values.
 *
 * @param color The background color of the style.
 * @param color_border The border color of the style.
 * @param translate The translation value for the style.
 * @param rotate The rotation value for the style.
 * @return A pointer to the newly created Style structure, or NULL if memory allocation fails.
 */
Style *create_style(char color, char color_border, float translate, float rotate)
{
    Style *style = malloc(sizeof(Style));
    if (style == NULL)
        return NULL;
    style->color = color;
    style->color_border = color_border;
    style->translate = translate;
    style->rotate = rotate;
    return style;
}

/**
 * @brief Frees the memory allocated for a Point structure.
 *
 * This function releases the memory occupied by the specified Point structure.
 *
 * @param point Pointer to the Point structure to be freed.
 */
void free_point(Point *point)
{
    free(point);
}

/**
 * @brief Frees the memory allocated for a Style structure.
 *
 * This function releases the memory occupied by the specified Style structure.
 *
 * @param style Pointer to the Style structure to be freed.
 */
void free_style(Style *style)
{
    free(style);
}

/**
 * @brief Frees the memory allocated for an Oval structure.
 *
 * This function releases the memory occupied by the specified Oval structure,
 * including its associated Point and Style structures.
 *
 * @param oval Pointer to the Oval structure to be freed.
 */
void free_oval(Oval *oval)
{
    if (oval == NULL)
        return;
    free_style(oval->S);
    free_point(oval->A);
    free(oval);
}

/**
 * @brief Frees the memory allocated for a Rectangle structure.
 *
 * This function releases the memory occupied by the specified Rectangle structure,
 * including its associated Point and Style structures.
 *
 * @param rectangle Pointer to the Rectangle structure to be freed.
 */
void free_rectangle(Rectangle *rectangle)
{
    if (rectangle == NULL)
        return;
    free_style(rectangle->S);
    free_point(rectangle->A);
    free(rectangle);
}

/**
 * @brief Frees the memory allocated for a Line structure.
 *
 * This function releases the memory occupied by the specified Line structure,
 * including its associated Point and Style structures.
 *
 * @param line Pointer to the Line structure to be freed.
 */
void free_line(Line *line)
{
    if (line == NULL)
        return;
    free_style(line->S);
    free_point(line->A);
    free_point(line->B);
    free(line);
}

/**
 * @brief Prints the properties of a Point structure to the console.
 *
 * This function displays the X and Y coordinates of the specified Point structure.
 *
 * @param point Pointer to the Point structure to be printed.
 */
void print_Point(Point *point)
{
    if (point == NULL)
        return;
    printf("POINT (%.2f %.2f)\n", point->x, point->y);
}

/**
 * @brief Prints the properties of a Style structure to the console.
 *
 * This function displays the color, border color, translation, and rotation
 * of the specified Style structure.
 *
 * @param style Pointer to the Style structure to be printed.
 */
void print_Style(Style *style)
{
    if (style == NULL)
        return;
    printf("STYLES (%c %c %.2f %.2f)\n", style->color, style->color_border, style->translate, style->rotate);
}

/**
 * @brief Prints the properties of a Rectangle structure to the console.
 *
 * This function displays the width, length, coordinates of point A, and style
 * of the specified Rectangle structure.
 *
 * @param rectangle Pointer to the Rectangle structure to be printed.
 */
void print_Rectangle(Rectangle *rectangle)
{
    if (rectangle == NULL)
        return;
    printf("RECTANGLE (%.2f %.2f)\n", rectangle->width, rectangle->length);
    print_Point(rectangle->A);
    print_Style(rectangle->S);
}

/**
 * @brief Prints the properties of an Oval structure to the console.
 *
 * This function displays the height radius, width_radius, coordinates of point A,
 * and style of the specified Oval structure.
 *
 * @param oval Pointer to the Oval structure to be printed.
 */
void print_Oval(Oval *oval)
{
    if (oval == NULL)
        return;
    printf("OVAL (%.2f %.2f)\n", oval->height_radius, oval->width_radius);
    print_Point(oval->A);
    print_Style(oval->S);
}

/**
 * @brief Prints the properties of a Line structure to the console.
 *
 * This function displays the coordinates of points A and B, as well as the style
 * of the specified Line structure.
 *
 * @param line Pointer to the Line structure to be printed.
 */
void print_Line(Line *line)
{
    if (line == NULL)
        return;
    printf("LINE\n");
    print_Point(line->A);
    print_Point(line->B);
    print_Style(line->S);
}

/**
 * @brief Asks the user for a floating-point value with a prompt message.
 *
 * This function displays the provided message to the user and reads a
 * floating-point value from standard input.
 *
 * @param message The prompt message to display to the user.
 * @return The floating-point value entered by the user.
 */
float ask_for_float(char *message)
{
    printf("%s", message);
    float v = 0.0f;
    scanf("%f", &v);
    return v;
}

/**
 * @brief Asks the user for an integer value with a prompt message.
 *
 * This function displays the provided message to the user and reads an
 * integer value from standard input.
 *
 * @param message The prompt message to display to the user.
 * @return The integer value entered by the user.
 */
int ask_for_int(char *message)
{
    printf("%s", message);
    int v = 0;
    scanf("%d", &v);
    return v;
}

/**
 * @brief Asks the user for a character value with a prompt message.
 *
 * This function displays the provided message to the user and reads a
 * character value from standard input.
 *
 * @param message The prompt message to display to the user.
 * @return The character value entered by the user.
 */
char ask_for_char(char *message)
{
    printf("%s", message);
    char v = '\0';
    scanf(" %c", &v);
    return v;
}

/**
 * @brief Asks the user for a Style structure with its properties.
 *
 * This function prompts the user to enter the color, border color,
 * translation, and rotation values for a Style structure. It then creates
 * and returns a new Style structure with the provided values.
 *
 * @return A pointer to the newly created Style structure, or NULL if memory allocation fails.
 */
Style *ask_for_style(void)
{
    char color = ask_for_char("What background color is preferred?\n");
    char color_border = ask_for_char("What border color would you like?\n");
    float translate = ask_for_float("Could you specify the translation you need?\n");
    float rotate = ask_for_float("Which rotation do you desire?\n");

    return create_style(color, color_border, translate, rotate);
}

/**
 * @brief Asks the user for a Point structure with its coordinates.
 *
 * This function prompts the user to enter the X and Y coordinates for a Point structure.
 * It then creates and returns a new Point structure with the provided coordinates.
 *
 * @return A pointer to the newly created Point structure, or NULL if memory allocation fails.
 */
Point *ask_for_point(void)
{
    return create_point(
        ask_for_float("Which rotation do you desire?\n"),
        ask_for_float("What is the desired longitude: y?\n"));
}

/**
 * @brief Asks the user for an Oval structure with its properties.
 *
 * This function prompts the user to enter the height radius, width_radius,
 * coordinates of point A, and style for an Oval structure. It then creates
 * and returns a new Oval structure with the provided values.
 *
 * @return A pointer to the newly created Oval structure, or NULL if memory allocation fails.
 */
Oval *ask_for_oval(void)
{
    float height_radius = ask_for_float("What is the desired height?\n");
    float width_radius = ask_for_float("What is the targeted width?\n");
    Point *point = ask_for_point();
    if (point == NULL)
        return NULL;
    Style *style = ask_for_style();
    if (style == NULL)
    {
        free_point(point);
        return NULL;
    }

    Oval *oval = create_oval(height_radius, width_radius, point, style);
    if (oval == NULL)
    {
        free_point(point);
        free_style(style);
    }
    return oval;
}

/**
 * @brief Asks the user for a Rectangle structure with its properties.
 *
 * This function prompts the user to enter the width, length, coordinates of point A,
 * and style for a Rectangle structure. It then creates and returns a new Rectangle
 * structure with the provided values.
 *
 * @return A pointer to the newly created Rectangle structure, or NULL if memory allocation fails.
 */
Rectangle *ask_for_rectangle(void)
{
    float width = ask_for_float("What is the targeted width?\n");
    float length = ask_for_float("What is the desired length?\n");
    Point *point = ask_for_point();
    if (point == NULL)
        return NULL;
    Style *style = ask_for_style();
    if (style == NULL)
    {
        free_point(point);
        return NULL;
    }

    Rectangle *rectangle = create_rectangle(width, length, point, style);
    if (rectangle == NULL)
    {
        free_point(point);
        free_style(style);
    }
    return rectangle;
}

/**
 * @brief Asks the user for a Line structure with its properties.
 *
 * This function prompts the user to enter the coordinates of points A and B,
 * as well as the style for a Line structure. It then creates and returns a new
 * Line structure with the provided values.
 *
 * @return A pointer to the newly created Line structure, or NULL if memory allocation fails.
 */
Line *ask_for_line(void)
{
    Point *point_a = ask_for_point();
    if (point_a == NULL)
        return NULL;
    Point *point_b = ask_for_point();
    if (point_b == NULL)
    {
        free_point(point_a);
        return NULL;
    }
    Style *style = ask_for_style();
    if (style == NULL)
    {
        free_point(point_a);
        free_point(point_b);
        return NULL;
    }

    Line *line = create_line(point_a, point_b, style);
    if (line == NULL)
    {
        free_point(point_a);
        free_point(point_b);
        free_style(style);
    }
    return line;
}
