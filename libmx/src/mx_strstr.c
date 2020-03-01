#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    char* tmphay = NULL;
    char* tmpnee = NULL;

    if (*needle == '\0')
        return (char*)haystack;
    while (*haystack != '\0') {
        tmphay = (char*)haystack;
        tmpnee = (char*)needle;
        while (*tmphay == *tmpnee && *tmphay != '\0' && *tmpnee != '\0') {
            tmpnee++;
            tmphay++;
        }
        if (*tmpnee == '\0')
            return (char*)haystack;
        haystack++;
     }
     return NULL;
}
