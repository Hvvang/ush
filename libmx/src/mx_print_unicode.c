#include "libmx.h"

static wchar_t check_if_0(wchar_t c, char* out);
static wchar_t check_if_1(wchar_t c, char* out);
static wchar_t check_if_2(wchar_t c, char* out);
static wchar_t check_if_3(wchar_t c, char* out);

void mx_print_unicode(wchar_t c) {
    char out[5];
    if (check_if_0(c, out)!= 0)
        write(1, out, mx_strlen(out));
    else if (check_if_1(c, out)!= 0)
        write(1, out, mx_strlen(out));
    else if (check_if_2(c, out)!= 0)
        write(1, out, mx_strlen(out));
    else if (check_if_3(c, out)!= 0)
       write(1, out, mx_strlen(out));
}

static wchar_t check_if_0(wchar_t c, char* out) {
    if (c < 0x80) {// < 128
        out[0] = (c >> 0 & 0x7F) | 0x00;
        out[1] = '\0';
        out[2] = '\0';
        out[3] = '\0';
        out[4] = '\0';
        return c;
    }
    else 
        return 0;
}

static wchar_t check_if_1(wchar_t c, char* out) {
    if (c < 0x0800) {// < 2048
        out[0] = (c >> 6 & 0x1F) | 0xC0;
        out[1] = (c >> 0 & 0x3F) | 0x80;
        out[2] = '\0';
        out[3] = '\0';
        out[4] = '\0';
        return c;
    }
    else 
        return 0;
}

static wchar_t check_if_2(wchar_t c, char* out) {
    if (c < 0x010000) {// < 65536
        out[0] = (c >> 12 & 0x0F) | 0xE0;
        out[1] = (c >> 6 & 0x3F) | 0x80;
        out[2] = (c >> 0 & 0x3F) | 0x80;
        out[3] = '\0';
        out[4] = '\0';
        return c;
    }
    else 
        return 0;
}

static wchar_t  check_if_3(wchar_t c, char* out) {
    if (c < 0x110000) {// < 1114112
        out[0] = (c >> 18 & 0x07) | 0xF0;
        out[1] = (c >> 12 & 0x3F) | 0x80;
        out[2] = (c >> 6 & 0x3F) | 0x80;
        out[3] = (c >> 0 & 0x3F) | 0x80;
        out[4] = '\0';
        return c;
    }
    else 
        return 0;
}
