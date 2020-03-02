#include "ush.h"

t_command *mx_parser(char *stdin_line) {
    t_command *_currentCommand = malloc(sizeof(t_command));
    t_SimpleCommand *_currentSipleCommand = malloc(sizeof(t_SimpleCommand));
    char **data = mx_strsplit(stdin_line, ' ');
    int j = 0;
    _currentSipleCommand->_arguments = malloc(sizeof(char *) * 8);

    for (int i = 0; data[i]; i++) {
        /* code */
        printf("data[%d] = \'%s\'\n", i, data[i]);
        printf("WORD : %d\n", mx_isWord(data[i]));
        printf("PIPE : %d\n", mx_isPipe(data[i]));
        printf("NEWLINE : %d\n", mx_isNewLine(data[i]));
        printf("GREAT : %d\n", mx_isGreat(data[i]));
        printf("LESS : %d\n", mx_isLess(data[i]));
        printf("GREATGREAT : %d\n", mx_isGreatGreat(data[i]));
        printf("GREATAMPERSAND : %d\n", mx_isGreatAmpersand(data[i]));
        printf("AMPERSAND : %d\n", mx_isAmpersand(data[i]));

        if (mx_isWord(data[i]) == WORD) {
            if (data[i][0] == '-') {
                _currentSipleCommand->_arguments[j++] = mx_strdup(data[i]);
            }
            else
                _currentSipleCommand->command = mx_strdup(data[i]);
        }
    }




    return _currentCommand;
}
