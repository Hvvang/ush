#include "mx_builtins.h"

#define MX_F_BLACK "\033[30m"
#define MX_B_BLACK "\033[40m"
#define MX_F_RED "\033[31m"
#define MX_B_RED "\033[41m"
#define MX_F_GREEN "\033[32m"
#define MX_B_GREEN "\033[42m"
#define MX_F_ORANGE "\033[33m"
#define MX_B_ORANGE "\033[43m"
#define MX_F_BLUE "\033[34m"
#define MX_B_BLUE "\033[44m"
#define MX_F_MAGENTA "\033[35m"
#define MX_B_MAGENTA "\033[45m"
#define MX_F_CYAN "\033[36m"
#define MX_B_CYAN "\033[46m"
#define MX_F_LIGHT_GREY "\033[37m"
#define MX_B_LIGHT_GREY "\033[47m"
#define MX_F_DEFAULT "\033[39m"
#define MX_B_DEFAULT "\033[49m"


static void print_color_table(void) {
    printf("Foreground\tBackground\n");
    printf("%sblack\033[0m\t\t%sblack\033[0m\n", MX_F_BLACK, MX_B_BLACK);
    printf("%sred\033[0m\t\t%sred\033[0m\n", MX_F_RED, MX_B_RED);
    printf("%sgreen\033[0m\t\t%sgreen\033[0m\n", MX_F_GREEN, MX_B_GREEN);
    printf("%sorange\033[0m\t\t%sorange\033[0m\n", MX_F_ORANGE, MX_B_ORANGE);
    printf("%sblue\033[0m\t\t%sblue\033[0m\n", MX_F_BLUE, MX_B_BLUE);
    printf("%smagenta\033[0m\t\t%smagenta\033[0m\n", MX_F_MAGENTA, MX_B_MAGENTA);
    printf("%scyan\033[0m\t\t%scyan\033[0m\n", MX_F_CYAN, MX_B_CYAN);
    printf("%slight-grey\033[0m\t%slight-grey\033[0m\n", MX_F_LIGHT_GREY, MX_B_LIGHT_GREY);
    printf("%sdefault\033[0m\t\t%sdefault\033[0m\n", MX_F_DEFAULT, MX_B_DEFAULT);

}

static void set_foreground_color(char *color) {
    if (!strcmp(color, "black"))
        printf(MX_F_BLACK);
    else if (!strcmp(color, "red"))
        printf(MX_F_RED);
    else if (!strcmp(color, "green"))
        printf(MX_F_GREEN);
    else if (!strcmp(color, "orange"))
        printf(MX_F_ORANGE);
    else if (!strcmp(color, "blue"))
        printf(MX_F_BLUE);
    else if (!strcmp(color, "magenta"))
        printf(MX_F_MAGENTA);
    else if (!strcmp(color, "cyan"))
        printf(MX_F_CYAN);
    else if (!strcmp(color, "lignt-grey"))
        printf(MX_F_LIGHT_GREY);
    else if (!strcmp(color, "default"))
        printf(MX_F_DEFAULT);
    else
        setenv("status", "1", 1);
}

static void set_background_color(char *color) {
    if (!strcmp(color, "black"))
        printf(MX_B_BLACK);
    else if (!strcmp(color, "red"))
        printf(MX_B_RED);
    else if (!strcmp(color, "green"))
        printf(MX_B_GREEN);
    else if (!strcmp(color, "orange"))
        printf(MX_B_ORANGE);
    else if (!strcmp(color, "blue"))
        printf(MX_B_BLUE);
    else if (!strcmp(color, "magenta"))
        printf(MX_B_MAGENTA);
    else if (!strcmp(color, "cyan"))
        printf(MX_B_CYAN);
    else if (!strcmp(color, "lignt-grey"))
        printf(MX_B_LIGHT_GREY);
    else if (!strcmp(color, "default"))
        printf(MX_B_DEFAULT);
    else
        setenv("status", "1", 1);
}

void mx_color(t_command *command) {
    int index = 0;
    char flag = mx_check_flags(MX_COLOR, &index, command, mx_valid_color);

    if (!atoi(getenv("status"))) {
        if (command->arguments[index]) {
            if (!strcmp(command->arguments[index], "usage"))
                printf("usage: color [-fb color] [-l] [-r]\n");
            else if (flag == 'f')
                set_foreground_color(command->arguments[index]);
            else if (flag == 'b')
                set_background_color(command->arguments[index]);
        }
        else if (flag == 'r') {
            set_background_color("default");
            set_foreground_color("default");
        }
        if (flag == 'l')
            print_color_table();
    }
}
