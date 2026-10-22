#ifndef SVG
#define SVG
#include <errno.h>
#include <stdio.h>
#include "formes.h"

#define SVG_CAPACITY 50

typedef enum
{
    RECTANGLE,
    OVALE,
    LIGNE
} EnumFormes;

typedef union
{
    Rectangle *rectangle;
    Ovale *ovale;
    Ligne *ligne;
} UnionFormes;

typedef struct
{
    EnumFormes *enumformes;
    UnionFormes *unionformes;
} Forme;

Forme *create_forme_at();

Forme *create_shape();

Forme **create_svg();

void free_svg(Forme **forme);

void print_formes(Forme *forme);

void free_forme(Forme *forme);

void modify_shape(Forme *forme);

void insert_new_shape_at(Forme **forme, size_t index);

void modify_shape_at(Forme **forme, size_t index);

void remove_shape_at(Forme **forme, size_t index);

void print_svg(Forme **forme);

int export_svg(Forme **forme, const char *filename);

void svg_rect(FILE *file, Rectangle *rectangle);

void svg_ellipse(FILE *file, Ovale *ovale);

void svg_line(FILE *file, Ligne *line);

#endif