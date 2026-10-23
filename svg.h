#ifndef SVG
#define SVG
#include <errno.h>
#include <stdio.h>
#include "shapes.h"

#define SVG_CAPACITY 50

typedef enum
{
    RECTANGLE,
    OVAL,
    LINE
} EnumShapes;

typedef union
{
    Rectangle *rectangle;
    Oval *oval;
    Line *line;
} UnionShapes;

typedef struct
{
    EnumShapes *enumshapes;
    UnionShapes *unionshapes;
} Shape;

Shape *create_shape_at();

Shape *create_shape();

Shape **create_svg();

void free_svg(Shape **shape);

void print_shapes(Shape *shape);

void free_shape(Shape *shape);

void modify_shape(Shape *shape);

void insert_new_shape_at(Shape **shape, size_t index);

void modify_shape_at(Shape **shape, size_t index);

void remove_shape_at(Shape **shape, size_t index);

void print_svg(Shape **shape);

int export_svg(Shape **shape, const char *filename);

void svg_rect(FILE *file, Rectangle *rectangle);

void svg_oval(FILE *file, Oval *oval);

void svg_line(FILE *file, Line *line);

#endif