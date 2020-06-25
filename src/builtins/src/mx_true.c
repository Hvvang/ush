#include "mx_builtins.h"

void mx_true(void) {
    setenv("status", "0", 1);
}
