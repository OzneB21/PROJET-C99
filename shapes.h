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

typedef struct oval
{
    float height_radius;
    float width_radius;
    Point *A;
    Style *S;
} Oval;

typedef struct rectangle
{
    float width;
    float length;
    Point *A;
    Style *S;
} Rectangle;

typedef struct line
{
    Point *A;
    Point *B;
    Style *S;
} Line;

Oval *create_oval(float height_radius, float width_radius, Point *A, Style *S);
Rectangle *create_rectangle(float width, float length, Point *A, Style *S);
Line *create_line(Point *A, Point *B, Style *S);
Point *create_point(float x, float y);
Style *create_style(char color, char color_border, float translate, float rotate);

void free_point(Point *point);
void free_style(Style *style);
void free_oval(Oval *oval);
void free_rectangle(Rectangle *rectangle);
void free_line(Line *line);

void print_Point(Point *point);
void print_Style(Style *style);
void print_Rectangle(Rectangle *rectangle);
void print_Oval(Oval *oval);
void print_Line(Line *line);

float ask_for_float(char *message);
int ask_for_int(char *message);
char ask_for_char(char *message);
Style *ask_for_style(void);
Point *ask_for_point(void);
Oval *ask_for_oval(void);
Rectangle *ask_for_rectangle(void);
Line *ask_for_line(void);

void modify_point(Point *point);
void modify_style(Style *style);
void modify_oval(Oval *oval);
void modify_rectangle(Rectangle *rectangle);
void modify_line(Line *line);

#endif