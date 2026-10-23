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
char *svg_color(char color)
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
void svg_style(FILE *file, Style *style, const char *fill)
{
    const char *stroke = style == NULL ? "black" : svg_color(style->color_border);
    float translate = style == NULL ? 0.0f : style->translate;
    float rotate = style == NULL ? 0.0f : style->rotate;
    fprintf(file,
            " fill=\"%s\" stroke=\"%s\" transform=\"translate(%.2f 0) rotate(%.2f)\"",
            fill, stroke, translate, rotate);
}

/**
 * @brief Creates a new Shape structure based on user input.
 *
 * This function prompts the user to select a shape type (Rectangle, Oval, or Line)
 * and gathers the necessary properties for the selected shape. It then creates and
 * returns a new Shape structure containing the selected shape and its properties.
 *
 * @return A pointer to the newly created Shape structure, or NULL if memory allocation fails or the shape is not available.
 */
Shape *create_shape()
{
    Shape *shape = calloc(1, sizeof(Shape));
    if (shape == NULL)
        return NULL;

    printf(" 1.LINE\n  2.OVAL\n  3.RECTANGLE\n");
    int choice = ask_for_int("Which shape do you choose?\n");
    EnumShapes *enum_shape = malloc(sizeof(EnumShapes));
    UnionShapes *union_shape = malloc(sizeof(UnionShapes));
    if (enum_shape == NULL || union_shape == NULL)
    {
        free(enum_shape);
        free(union_shape);
        free(shape);
        return NULL;
    }

    // demander à l'utilisateur
    switch (choice)
    {
    case 1:
        *enum_shape = LINE;
        union_shape->line = ask_for_line();
        break;

    case 2:
        *enum_shape = OVAL;
        union_shape->oval = ask_for_oval();
        break;

    case 3:
        *enum_shape = RECTANGLE;
        union_shape->rectangle = ask_for_rectangle();
        break;

    default:
        printf("Shape not available");
        free(enum_shape);
        free(union_shape);
        free(shape);
        return NULL;
    }

    if ((*enum_shape == LINE && union_shape->line == NULL) ||
        (*enum_shape == OVAL && union_shape->oval == NULL) ||
        (*enum_shape == RECTANGLE && union_shape->rectangle == NULL))
    {
        free(enum_shape);
        free(union_shape);
        free(shape);
        return NULL;
    }

    // Creer l'union + mettre la shape dans l'union
    shape->enumshapes = enum_shape;
    shape->unionshapes = union_shape;
    return shape;
}

/**
 * @brief Modifies the properties of a Shape structure based on user input.
 *
 * This function checks the type of shape contained in the Shape structure and
 * calls the appropriate modification function for that shape (Line, Oval, or Rectangle).
 * The user can modify the properties of the shape through a menu-driven interface.
 *
 * @param shape Pointer to the Shape structure to be modified.
 */
void modify_shape(Shape *shape)
{
    if (shape == NULL || shape->enumshapes == NULL || shape->unionshapes == NULL)
        return;
    switch (*shape->enumshapes)
    {
    case LINE:
        modify_line(shape->unionshapes->line);
        break;
    case OVAL:
        modify_oval(shape->unionshapes->oval);
        break;
    case RECTANGLE:
        modify_rectangle(shape->unionshapes->rectangle);
        break;

    default:
        break;
    }
}
void print_shapes(Shape *shape)
{
    if (shape == NULL)
        return;
    switch (*shape->enumshapes)
    {
    case LINE:
        print_Line(shape->unionshapes->line);
        break;

    case OVAL:
        print_Oval(shape->unionshapes->oval);
        break;

    case RECTANGLE:
        print_Rectangle(shape->unionshapes->rectangle);
        break;

    default:
        break;
    }
}

void free_shape(Shape *shape)
{
    if (shape == NULL)
        return;

    // free le contenu avant
    if (shape->enumshapes != NULL && shape->unionshapes != NULL)
    {
        switch (*shape->enumshapes)
        {
        case LINE:
            free_line(shape->unionshapes->line);
            break;
        case OVAL:
            free_oval(shape->unionshapes->oval);
            break;
        case RECTANGLE:
            free_rectangle(shape->unionshapes->rectangle);
            break;
        default:
            break;
        }
    }

    free(shape->enumshapes);
    free(shape->unionshapes);
    free(shape);
}

/**
 * @brief Creates an array of Shape pointers to represent an SVG canvas.
 *
 * This function allocates memory for an array of Shape pointers, with a capacity
 * defined by SVG_CAPACITY. Each element in the array is initialized to NULL.
 *
 * @return A pointer to the newly created array of Shape pointers, or NULL if memory allocation fails.
 */
Shape **create_svg()
{
    Shape **shape = malloc(SVG_CAPACITY * sizeof(Shape *));
    if (shape == NULL)
        return NULL;
    for (size_t i = 0; i < SVG_CAPACITY; i++)
        shape[i] = NULL;
    return shape;
}

void insert_new_shape_at(Shape **shape, size_t index)
{
    if (shape == NULL)
        return;
    if (index >= SVG_CAPACITY)
        return;
    Shape *new_shape = create_shape();
    if (new_shape == NULL)
        return;
    free_shape(shape[index]);
    shape[index] = new_shape;
}

/**
 * @brief Modifies the properties of a Shape structure at a specified index in an array.
 *
 * This function checks if the provided index is valid and if the Shape pointer at that
 * index is not NULL. If both conditions are met, it calls the modify_shape function to
 * allow the user to modify the properties of the Shape structure at that index.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 * @param index The index of the Shape structure to be modified.
 */
void modify_shape_at(Shape **shape, size_t index)
{
    if (shape == NULL)
        return;
    if (index >= SVG_CAPACITY)
        return;
    Shape *shape_to_modify = shape[index];
    modify_shape(shape_to_modify);
}

/**
 * @brief Removes a Shape structure at a specified index in an array.
 *
 * This function checks if the provided index is valid and if the Shape pointer at that
 * index is not NULL. If both conditions are met, it frees the memory allocated for the
 * Shape structure at that index and sets the pointer to NULL.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 * @param index The index of the Shape structure to be removed.
 */
void remove_shape_at(Shape **shape, size_t index)
{
    if (shape == NULL || index >= SVG_CAPACITY)
        return;
    free_shape(shape[index]);
    shape[index] = NULL;
}

/**
 * @brief Frees the memory allocated for an array of Shape pointers.
 *
 * This function iterates through the array of Shape pointers, freeing each
 * individual Shape structure using the free_shape function. After all
 * Shape structures have been freed, it frees the memory allocated for the
 * array itself.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 */
void free_svg(Shape **shape)
{
    if (shape == NULL)
        return;

    for (size_t i = 0; i < SVG_CAPACITY; i++)
        free_shape(shape[i]);
    free(shape);
}

/**
 * @brief Prints the properties of all Shape structures in an array to the console.
 *
 * This function iterates through the array of Shape pointers and calls the
 * print_shapes function for each non-NULL Shape structure, displaying their
 * properties to the console.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 */
void print_svg(Shape **shape)
{
    if (shape == NULL)
        return;

    for (size_t i = 0; i < SVG_CAPACITY; i++)
        if (shape[i] != NULL)
            print_shapes(shape[i]);
}

/**
 * @brief Exports the properties of all Shape structures in an array to an SVG file.
 *
 * This function creates an SVG file with the specified filename and writes the
 * properties of each Shape structure in the array to the file in SVG format.
 * It handles errors related to file operations and returns an appropriate error code.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 * @param filename The name of the SVG file to be created.
 * @return 0 on success, -1 on failure (with errno set).
 */
void svg_rectangle(FILE *file, Rectangle *rectangle)
{
    if (file == NULL || rectangle == NULL || rectangle->A == NULL)
        return;

    fprintf(file, "  <rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"",
            rectangle->A->x, rectangle->A->y, rectangle->width, rectangle->length);
    svg_style(file, rectangle->S,
              rectangle->S == NULL ? "black" : svg_color(rectangle->S->color));
    fprintf(file, " />\n");
}

/**
 * @brief Writes the properties of an Oval structure to an SVG file.
 *
 * This function generates the SVG representation of an Oval structure and writes
 * it to the specified file. It includes the center coordinates, radii, and style
 * attributes for the Oval.
 *
 * @param file The file pointer to write the SVG representation to.
 * @param oval Pointer to the Oval structure to be exported.
 */
void svg_oval(FILE *file, Oval *oval)
{
    if (file == NULL || oval == NULL || oval->A == NULL)
        return;

    fprintf(file, "  <ellipse cx=\"%.2f\" cy=\"%.2f\" rx=\"%.2f\" ry=\"%.2f\"",
            oval->A->x, oval->A->y, oval->width_radius, oval->height_radius);
    svg_style(file, oval->S,
              oval->S == NULL ? "black" : svg_color(oval->S->color));
    fprintf(file, " />\n");
}

/**
 * @brief Writes the properties of a Line structure to an SVG file.
 *
 * This function generates the SVG representation of a Line structure and writes
 * it to the specified file. It includes the coordinates of the two endpoints
 * and style attributes for the Line.
 *
 * @param file The file pointer to write the SVG representation to.
 * @param line Pointer to the Line structure to be exported.
 */
void svg_line(FILE *file, Line *line)
{
    if (file == NULL || line == NULL || line->A == NULL || line->B == NULL)
        return;

    fprintf(file, "  <line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\"",
            line->A->x, line->A->y, line->B->x, line->B->y);
    svg_style(file, line->S, "none");
    fprintf(file, " />\n");
}

/**
 * @brief Exports the properties of all Shape structures in an array to an SVG file.
 *
 * This function creates an SVG file with the specified filename and writes the
 * properties of each Shape structure in the array to the file in SVG format.
 * It handles errors related to file operations and returns an appropriate error code.
 *
 * @param shape An array of Shape pointers representing the SVG canvas.
 * @param filename The name of the SVG file to be created.
 * @return 0 on success, -1 on failure (with errno set).
 */
int export_svg(Shape **form, const char *filename)
{
    if (form == NULL || filename == NULL)
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
        Shape *shape = form[i];
        if (shape == NULL || shape->enumshapes == NULL || shape->unionshapes == NULL)
            continue;

        switch (*shape->enumshapes)
        {
        case RECTANGLE:
            svg_rectangle(file, shape->unionshapes->rectangle);
            break;
        case OVAL:
            svg_oval(file, shape->unionshapes->oval);
            break;
        case LINE:
            svg_line(file, shape->unionshapes->line);
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
