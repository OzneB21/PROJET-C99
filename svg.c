#include "svg.h"
#include <errno.h>
#include <stdlib.h>
#include <errno.h>
/**
 * @brief Converts a character representing a color to its corresponding SVG color name.
 *
 * This function takes a character input representing a color and returns the
 * corresponding SVG color name as a string. If the input character does not
 * match any predefined colors, it defaults to "black".
 *
 * @param color The character representing the color (e.g., 'r' for red, 'g' for green).
 * @return A string representing the SVG color name.
 */
static const char *svg_color(char color)
{
    switch (color)
    {
    case 'r':
    case 'R':
        return "red";
    case 'g':
    case 'G':
        return "green";
    case 'b':
    case 'B':
        return "blue";
    case 'y':
    case 'Y':
        return "yellow";
    case 'c':
    case 'C':
        return "cyan";
    case 'm':
    case 'M':
        return "magenta";
    case 'w':
    case 'W':
        return "white";
    case 'k':
    case 'K':
        return "black";
    default:
        return "black";
    }
}

/**
 * @brief Writes the style attributes for an SVG element to a file.
 *
 * This function writes the fill color, stroke color, translation, and rotation
 * attributes for an SVG element to the specified file. If the provided Style
 * structure is NULL, default values are used.
 *
 * @param file The file pointer to write the SVG attributes to.
 * @param style Pointer to the Style structure containing the style properties.
 * @param fill The fill color for the SVG element.
 */
static void svg_style(FILE *file, Style *style, const char *fill)
{
    const char *stroke = style == NULL ? "black" : svg_color(style->color_border);
    float translate = style == NULL ? 0.0f : style->translate;
    float rotate = style == NULL ? 0.0f : style->rotate;
    fprintf(file,
            " fill=\"%s\" stroke=\"%s\" transform=\"translate(%.2f 0) rotate(%.2f)\"",
            fill, stroke, translate, rotate);
}

/**
 * @brief Creates a new Forme structure based on user input.
 *
 * This function prompts the user to select a shape type (Rectangle, Ovale, or Ligne)
 * and gathers the necessary properties for the selected shape. It then creates and
 * returns a new Forme structure containing the selected shape and its properties.
 *
 * @return A pointer to the newly created Forme structure, or NULL if memory allocation fails or the shape is not available.
 */
Forme *create_shape()
{
    Forme *forme = calloc(1, sizeof(Forme));
    if (forme == NULL)
        return NULL;
    // Creer l'enum et demander a l'utilisateur quelle forme ?

    printf(" 1.LIGNE\n  2.OVALE\n  3.RECTANGLE\n");
    int choice = ask_for_int("Which shape do you choose?\n");
    EnumFormes *enum_forme = malloc(sizeof(EnumFormes));
    UnionFormes *union_forme = malloc(sizeof(UnionFormes));
    if (enum_forme == NULL || union_forme == NULL)
    {
        free(enum_forme);
        free(union_forme);
        free(forme);
        return NULL;
    }

    // demander à l'utilisateur
    switch (choice)
    {
    case 1:
        *enum_forme = LIGNE;
        union_forme->ligne = ask_for_ligne();
        break;

    case 2:
        *enum_forme = OVALE;
        union_forme->ovale = ask_for_ovale();
        break;

    case 3:
        *enum_forme = RECTANGLE;
        union_forme->rectangle = ask_for_rectangle();
        break;

    default:
        printf("Shape not available");
        free(enum_forme);
        free(union_forme);
        free(forme);
        return NULL;
    }

    if ((*enum_forme == LIGNE && union_forme->ligne == NULL) ||
        (*enum_forme == OVALE && union_forme->ovale == NULL) ||
        (*enum_forme == RECTANGLE && union_forme->rectangle == NULL))
    {
        free(enum_forme);
        free(union_forme);
        free(forme);
        return NULL;
    }

    // Creer l'union + mettre la forme dans l'union
    forme->enumformes = enum_forme;
    forme->unionformes = union_forme;
    return forme;
}

/**
 * @brief Modifies the properties of a Forme structure based on user input.
 *
 * This function checks the type of shape contained in the Forme structure and
 * calls the appropriate modification function for that shape (Ligne, Ovale, or Rectangle).
 * The user can modify the properties of the shape through a menu-driven interface.
 *
 * @param forme Pointer to the Forme structure to be modified.
 */
void modify_shape(Forme *forme)
{
    if (forme == NULL || forme->enumformes == NULL || forme->unionformes == NULL)
        return;
    switch (*forme->enumformes)
    {
    case LIGNE:
        modify_ligne(forme->unionformes->ligne);
        break;
    case OVALE:
        modify_ovale(forme->unionformes->ovale);
        break;
    case RECTANGLE:
        modify_rectangle(forme->unionformes->rectangle);
        break;

    default:
        break;
    }
}
void print_formes(Forme *forme)
{
    if (forme == NULL)
        return;
    switch (*forme->enumformes)
    {
    case LIGNE:
        print_Ligne(forme->unionformes->ligne);
        break;

    case OVALE:
        print_Ovale(forme->unionformes->ovale);
        break;

    case RECTANGLE:
        print_Rectangle(forme->unionformes->rectangle);
        break;

    default:
        break;
    }
}

void free_forme(Forme *forme)
{
    if (forme == NULL)
        return;

    // free le contenu avant
    if (forme->enumformes != NULL && forme->unionformes != NULL)
    {
        switch (*forme->enumformes)
        {
        case LIGNE:
            free_ligne(forme->unionformes->ligne);
            break;
        case OVALE:
            free_ovale(forme->unionformes->ovale);
            break;
        case RECTANGLE:
            free_rectangle(forme->unionformes->rectangle);
            break;
        default:
            break;
        }
    }

    free(forme->enumformes);
    free(forme->unionformes);
    free(forme);
}

/**
 * @brief Creates an array of Forme pointers to represent an SVG canvas.
 *
 * This function allocates memory for an array of Forme pointers, with a capacity
 * defined by SVG_CAPACITY. Each element in the array is initialized to NULL.
 *
 * @return A pointer to the newly created array of Forme pointers, or NULL if memory allocation fails.
 */
Forme **create_svg()
{
    Forme **forme = malloc(SVG_CAPACITY * sizeof(Forme *));
    if (forme == NULL)
        return NULL;
    for (size_t i = 0; i < SVG_CAPACITY; i++)
        forme[i] = NULL;
    return forme;
}

void insert_new_shape_at(Forme **forme, size_t index)
{
    if (forme == NULL)
        return;
    if (index >= SVG_CAPACITY)
        return;
    Forme *new_forme = create_shape();
    if (new_forme == NULL)
        return;
    free_forme(forme[index]);
    forme[index] = new_forme;
}

/**
 * @brief Modifies the properties of a Forme structure at a specified index in an array.
 *
 * This function checks if the provided index is valid and if the Forme pointer at that
 * index is not NULL. If both conditions are met, it calls the modify_shape function to
 * allow the user to modify the properties of the Forme structure at that index.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 * @param index The index of the Forme structure to be modified.
 */
void modify_shape_at(Forme **forme, size_t index)
{
    if (forme == NULL)
        return;
    if (index >= SVG_CAPACITY)
        return;
    Forme *forme_to_modify = forme[index];
    modify_shape(forme_to_modify);
}

/**
 * @brief Removes a Forme structure at a specified index in an array.
 *
 * This function checks if the provided index is valid and if the Forme pointer at that
 * index is not NULL. If both conditions are met, it frees the memory allocated for the
 * Forme structure at that index and sets the pointer to NULL.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 * @param index The index of the Forme structure to be removed.
 */
void remove_shape_at(Forme **forme, size_t index)
{
    if (forme == NULL || index >= SVG_CAPACITY)
        return;
    free_forme(forme[index]);
    forme[index] = NULL;
}

/**
 * @brief Frees the memory allocated for an array of Forme pointers.
 *
 * This function iterates through the array of Forme pointers, freeing each
 * individual Forme structure using the free_forme function. After all
 * Forme structures have been freed, it frees the memory allocated for the
 * array itself.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 */
void free_svg(Forme **forme)
{
    if (forme == NULL)
        return;

    for (size_t i = 0; i < SVG_CAPACITY; i++)
        free_forme(forme[i]);
    free(forme);
}

/**
 * @brief Prints the properties of all Forme structures in an array to the console.
 *
 * This function iterates through the array of Forme pointers and calls the
 * print_formes function for each non-NULL Forme structure, displaying their
 * properties to the console.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 */
void print_svg(Forme **forme)
{
    if (forme == NULL)
        return;

    for (size_t i = 0; i < SVG_CAPACITY; i++)
        if (forme[i] != NULL)
            print_formes(forme[i]);
}

/**
 * @brief Exports the properties of all Forme structures in an array to an SVG file.
 *
 * This function creates an SVG file with the specified filename and writes the
 * properties of each Forme structure in the array to the file in SVG format.
 * It handles errors related to file operations and returns an appropriate error code.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 * @param filename The name of the SVG file to be created.
 * @return 0 on success, -1 on failure (with errno set).
 */
void svg_rectangle(FILE *file, Rectangle *rectangle)
{
    if (file == NULL || rectangle == NULL || rectangle->A == NULL)
        return;

    fprintf(file, "  <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"",
            rectangle->A->x, rectangle->A->y, rectangle->largeur, rectangle->longueur);
    svg_style(file, rectangle->S,
              rectangle->S == NULL ? "black" : svg_color(rectangle->S->color));
    fprintf(file, " />\n");
}

/**
 * @brief Writes the properties of an Ovale structure to an SVG file.
 *
 * This function generates the SVG representation of an Ovale structure and writes
 * it to the specified file. It includes the center coordinates, radii, and style
 * attributes for the Ovale.
 *
 * @param file The file pointer to write the SVG representation to.
 * @param ovale Pointer to the Ovale structure to be exported.
 */
void svg_ovale(FILE *file, Ovale *ovale)
{
    if (file == NULL || ovale == NULL || ovale->A == NULL)
        return;

    fprintf(file, "  <ellipse cx=\"%.2f\" cy=\"%.2f\" rx=\"%.2f\" ry=\"%.2f\"",
            ovale->A->x, ovale->A->y, ovale->rayon_largeur, ovale->rayon_hauteur);
    svg_style(file, ovale->S,
              ovale->S == NULL ? "black" : svg_color(ovale->S->color));
    fprintf(file, " />\n");
}

/**
 * @brief Writes the properties of a Ligne structure to an SVG file.
 *
 * This function generates the SVG representation of a Ligne structure and writes
 * it to the specified file. It includes the coordinates of the two endpoints
 * and style attributes for the Ligne.
 *
 * @param file The file pointer to write the SVG representation to.
 * @param line Pointer to the Ligne structure to be exported.
 */
void svg_line(FILE *file, Ligne *line)
{
    if (file == NULL || line == NULL || line->A == NULL || line->B == NULL)
        return;

    fprintf(file, "  <line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\"",
            line->A->x, line->A->y, line->B->x, line->B->y);
    svg_style(file, line->S, "none");
    fprintf(file, " />\n");
}

/**
 * @brief Exports the properties of all Forme structures in an array to an SVG file.
 *
 * This function creates an SVG file with the specified filename and writes the
 * properties of each Forme structure in the array to the file in SVG format.
 * It handles errors related to file operations and returns an appropriate error code.
 *
 * @param forme An array of Forme pointers representing the SVG canvas.
 * @param filename The name of the SVG file to be created.
 * @return 0 on success, -1 on failure (with errno set).
 */
int export_svg(Forme **forme, const char *filename)
{
    if (forme == NULL || filename == NULL)
    {
        errno = EINVAL;
        return -1;
    }

    FILE *file = fopen(filename, "w");
    if (file == NULL)
        return -1;

    int failed = fprintf(file,
                         "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                         "<svg xmlns=\"http://www.w3.org/2000/svg\" "
                         "width=\"1000\" height=\"1000\" viewBox=\"0 0 1000 1000\">\n") < 0;

    for (size_t i = 0; !failed && i < SVG_CAPACITY; i++)
    {
        Forme *shape = forme[i];
        if (shape == NULL || shape->enumformes == NULL || shape->unionformes == NULL)
            continue;

        switch (*shape->enumformes)
        {
        case RECTANGLE:
            svg_rectangle(file, shape->unionformes->rectangle);
            break;
        case OVALE:
            svg_ovale(file, shape->unionformes->ovale);
            break;
        case LIGNE:
            svg_line(file, shape->unionformes->ligne);
            break;
        default:
            continue;
        }
        failed = ferror(file);
    }

    if (!failed && fprintf(file, "</svg>\n") < 0)
        failed = 1;
    if (fclose(file) != 0)
        failed = 1;

    if (failed)
    {
        errno = EIO;
        return -1;
    }
    return 0;
}
