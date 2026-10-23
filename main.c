#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "shapes.h"
#include "svg.h"
#include "color.h"

/**
 * @brief Asks the user for a shape index and validates it.
 *
 * @return The validated shape index, or -1 if invalid.
 */
int ask_shape_index(void)
{
    int index = ask_for_int("Shape index (0-49): ");
    if (index < 0 || index >= SVG_CAPACITY)
    {
        printf("Invalid shape index. Choose a value from 0 to 49.\n");
        return -1;
    }
    return index;
}
/**
 * @brief Main function for the SVG shape management program.
 *
 * @return EXIT_SUCCESS on successful execution, EXIT_FAILURE on error.
 */
int main(void)
{

    char menu;
    Shape **svg = create_svg();
    if (svg == NULL)
    {
        fprintf(stderr, "Unable to allocate the shape collection.\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        printf(BOLD_MAGENTA "===========================================[MENU]================================================"
                            "\n" RESET);
        printf(BOLD_WHITE " |                                                                                             |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||----------|   ||               ||               ||----------||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||----------|   ||               ||               ||----------||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||              ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||              ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     || ---------- ||   ||----------|   ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     || ---------- ||   ||----------|   ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||              ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||              ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||              ||               ||               ||          ||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||----------|   ||----------|    ||----------|    ||----------||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |     ||            ||   ||----------|   ||----------|    ||----------|    ||----------||     |"
                          "\n" RESET);
        printf(BOLD_WHITE " |                                                                                             |"
                          "\n" RESET);
        printf(BOLD_MAGENTA "===========================================[MENU]================================================"
                            "\n" RESET);

        printf(BOLD_MAGENTA "    ============[MENU]============\n" RESET);
        printf("    |   " BOLD_CYAN "1" RESET BOLD_YELLOW " -" UNDERLINE "Create a new shape" RESET
               "   |   \n");
        printf("    |   " BOLD_CYAN "2" RESET BOLD_YELLOW " -" UNDERLINE "Modify the shape" RESET
               "     |   \n");
        printf("    |   " BOLD_CYAN "3" RESET BOLD_YELLOW " -" UNDERLINE "Erased the shape" RESET
               "     |   \n");
        printf("    |   " BOLD_CYAN "4" RESET BOLD_YELLOW " -" UNDERLINE "Display all shape" RESET
               "    |   \n");
        printf("    |   " BOLD_CYAN "5" RESET BOLD_YELLOW " -" UNDERLINE "Export in SVG" RESET
               "        |   \n");
        printf("    |   " BOLD_CYAN "6" RESET BOLD_YELLOW " -" UNDERLINE "Quit" RESET
               "                 |   \n");
        printf(BOLD_MAGENTA "    ============[MENU]============\n" RESET);
        printf(BOLD "Your choice :  \n" RESET);

        if (scanf(" %c", &menu) != 1)
            break;

        system("clear");

        switch (menu)
        {
        case '1':
            printf(BOLD_CYAN "\n[CREATION]\n" RESET);
            {
                int index = ask_shape_index();
                if (index >= 0)
                    insert_new_shape_at(svg, (size_t)index);
            }
            break;

        case '2':
            printf(BOLD_CYAN "\n[MODIFICATION]\n" RESET);
            {
                int index = ask_shape_index();
                if (index >= 0)
                    modify_shape_at(svg, (size_t)index);
            }
            break;

        case '3':
            printf(BOLD_CYAN "\n[DELETE]\n" RESET);
            {
                int index = ask_shape_index();
                if (index >= 0)
                    remove_shape_at(svg, (size_t)index);
            }
            break;

        case '4':
            printf(BOLD_CYAN "\n[DISPLAY]\n" RESET);
            print_svg(svg);
            break;

        case '5':
            printf(BOLD_CYAN "\n[EXPORT]\n" RESET);
            if (export_svg(svg, "output.svg") == 0)
                printf("SVG exported to output.svg\n");
            else
                perror("Unable to export output.svg");
            break;

        case '6':
        {
            printf("Do you want to quit ?\n");
            printf(" 1 - YES \n");
            printf(" 2 - NO\n");
            char user_choice;
            if (scanf(" %c", &user_choice) == 1 && user_choice == '1')
            {
                free_svg(svg);
                printf("Goodbye!\n");
                return EXIT_SUCCESS;
            }
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    free_svg(svg);
    return EXIT_SUCCESS;
}