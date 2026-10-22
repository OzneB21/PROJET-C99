#ifndef SHAPES
#define SHAPES

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
    float x;
    float y;
} Point;

typedef struct styles
{
    char color;
    char color_border;
    float translate;
    float rotate;
} Style;

typedef struct ovale
{
    float rayon_hauteur;
    float rayon_largeur;
    Point *A;
    Style *S;
} Ovale;

typedef struct rectangle
{
    float largeur;
    float longueur;
    Point *A;
    Style *S;
} Rectangle;

typedef struct ligne
{
    Point *A;
    Point *B;
    Style *S;
} Ligne;

Ovale *create_ovale(float rayon_hauteur, float rayon_largeur, Point *A, Style *S);
Rectangle *create_rectangle(float largeur, float longueur, Point *A, Style *S);
Ligne *create_ligne(Point *A, Point *B, Style *S);
Point *create_point(float x, float y);
Style *create_style(char color, char color_border, float translate, float rotate);

void free_point(Point *point);
void free_style(Style *style);
void free_ovale(Ovale *ovale);
void free_rectangle(Rectangle *rectangle);
void free_ligne(Ligne *ligne);

void print_Point(Point *point);
void print_Style(Style *style);
void print_Rectangle(Rectangle *rectangle);
void print_Ovale(Ovale *ovale);
void print_Ligne(Ligne *ligne);

float ask_for_float(char *message);
int ask_for_int(char *message);
char ask_for_char(char *message);
Style *ask_for_style(void);
Point *ask_for_point(void);
Ovale *ask_for_ovale(void);
Rectangle *ask_for_rectangle(void);
Ligne *ask_for_ligne(void);

void modify_point(Point *point);
void modify_style(Style *style);
void modify_ovale(Ovale *ovale);
void modify_rectangle(Rectangle *rectangle);
void modify_ligne(Ligne *ligne);

#endif