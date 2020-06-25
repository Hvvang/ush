#include "mx_builtins.h"

void mx_false(void) {
    setenv("status", "1", 1);
}
