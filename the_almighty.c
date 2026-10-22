#include <stdio.h>
#include <stdlib.h>
#include "formes.h"
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
Ovale *create_ovale(float rayon_hauteur, float rayon_largeur, Point *A, Style *S)
{
    Ovale *ovale = malloc(sizeof(Ovale));
    if (ovale == NULL)
        return NULL;
    ovale->A = A;
    ovale->S = S;
    ovale->rayon_hauteur = rayon_hauteur;
    ovale->rayon_largeur = rayon_largeur;
    return ovale;
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
Rectangle *create_rectangle(float largeur, float longueur, Point *A, Style *S)
{
    Rectangle *rectangle = malloc(sizeof(Rectangle));
    if (rectangle == NULL)
        return NULL;
    rectangle->A = A;
    rectangle->S = S;
    rectangle->largeur = largeur;
    rectangle->longueur = longueur;
    return rectangle;
}

/**
 * @brief Modifies the properties of a Ligne structure based on user input.
 *
 * This function presents a menu to the user, allowing them to modify the
 * coordinates of points A and B, as well as the style of the Ligne. The user
 * can choose to modify each property or exit the modification process.
 *
 * @param ligne Pointer to the Ligne structure to be modified.
 */
Ligne *create_ligne(Point *A, Point *B, Style *S)
{
    Ligne *ligne = malloc(sizeof(Ligne));
    if (ligne == NULL)
        return NULL;
    ligne->A = A;
    ligne->B = B;
    ligne->S = S;
    return ligne;
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
 * @brief Frees the memory allocated for an Ovale structure.
 *
 * This function releases the memory occupied by the specified Ovale structure,
 * including its associated Point and Style structures.
 *
 * @param ovale Pointer to the Ovale structure to be freed.
 */
void free_ovale(Ovale *ovale)
{
    if (ovale == NULL)
        return;
    free_style(ovale->S);
    free_point(ovale->A);
    free(ovale);
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
 * @brief Frees the memory allocated for a Ligne structure.
 *
 * This function releases the memory occupied by the specified Ligne structure,
 * including its associated Point and Style structures.
 *
 * @param ligne Pointer to the Ligne structure to be freed.
 */
void free_ligne(Ligne *ligne)
{
    if (ligne == NULL)
        return;
    free_style(ligne->S);
    free_point(ligne->A);
    free_point(ligne->B);
    free(ligne);
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
    printf("RECTANGLE (%.2f %.2f)\n", rectangle->largeur, rectangle->longueur);
    print_Point(rectangle->A);
    print_Style(rectangle->S);
}

/**
 * @brief Prints the properties of an Ovale structure to the console.
 *
 * This function displays the height radius, width radius, coordinates of point A,
 * and style of the specified Ovale structure.
 *
 * @param ovale Pointer to the Ovale structure to be printed.
 */
void print_Ovale(Ovale *ovale)
{
    if (ovale == NULL)
        return;
    printf("OVALE (%.2f %.2f)\n", ovale->rayon_hauteur, ovale->rayon_largeur);
    print_Point(ovale->A);
    print_Style(ovale->S);
}

/**
 * @brief Prints the properties of a Ligne structure to the console.
 *
 * This function displays the coordinates of points A and B, as well as the style
 * of the specified Ligne structure.
 *
 * @param ligne Pointer to the Ligne structure to be printed.
 */
void print_Ligne(Ligne *ligne)
{
    if (ligne == NULL)
        return;
    printf("LIGNE\n");
    print_Point(ligne->A);
    print_Point(ligne->B);
    print_Style(ligne->S);
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
    char color = ask_for_char("Quelle couleur de fond voulez-vous?\n");
    char color_border = ask_for_char("Quelle couleur pour la bordure voulez-vous?\n");
    float translate = ask_for_float("Quelle est la translation que vous souhaitez?\n");
    float rotate = ask_for_float("Quelle est la rotation que vous souhaitez?\n");

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
        ask_for_float("Quelle est la latitude : x souhaitée?\n"),
        ask_for_float("Quelle est la longitude : y souhaitée?\n"));
}

/**
 * @brief Asks the user for an Ovale structure with its properties.
 *
 * This function prompts the user to enter the height radius, width radius,
 * coordinates of point A, and style for an Ovale structure. It then creates
 * and returns a new Ovale structure with the provided values.
 *
 * @return A pointer to the newly created Ovale structure, or NULL if memory allocation fails.
 */
Ovale *ask_for_ovale(void)
{
    float rayon_hauteur = ask_for_float("Quelle est la hauteur souhaitée?\n");
    float rayon_largeur = ask_for_float("Quelle est la largeur souhaitée?\n");
    Point *point = ask_for_point();
    if (point == NULL)
        return NULL;
    Style *style = ask_for_style();
    if (style == NULL)
    {
        free_point(point);
        return NULL;
    }

    Ovale *ovale = create_ovale(rayon_hauteur, rayon_largeur, point, style);
    if (ovale == NULL)
    {
        free_point(point);
        free_style(style);
    }
    return ovale;
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
    float largeur = ask_for_float("Quelle est la largeur souhaitée?\n");
    float longueur = ask_for_float("Quelle est la longueur souhaitée?\n");
    Point *point = ask_for_point();
    if (point == NULL)
        return NULL;
    Style *style = ask_for_style();
    if (style == NULL)
    {
        free_point(point);
        return NULL;
    }

    Rectangle *rectangle = create_rectangle(largeur, longueur, point, style);
    if (rectangle == NULL)
    {
        free_point(point);
        free_style(style);
    }
    return rectangle;
}

/**
 * @brief Asks the user for a Ligne structure with its properties.
 *
 * This function prompts the user to enter the coordinates of points A and B,
 * as well as the style for a Ligne structure. It then creates and returns a new
 * Ligne structure with the provided values.
 *
 * @return A pointer to the newly created Ligne structure, or NULL if memory allocation fails.
 */
Ligne *ask_for_ligne(void)
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

    Ligne *ligne = create_ligne(point_a, point_b, style);
    if (ligne == NULL)
    {
        free_point(point_a);
        free_point(point_b);
        free_style(style);
    }
    return ligne;
}
