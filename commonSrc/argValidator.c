#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

int validate_ip(const char *ipOriginal) {
    int dots = 0;
    char ip[strlen(ipOriginal)];
    strcpy(ip, ipOriginal);

    const char *ptr = strtok(ip, ".");
    if (ptr == NULL)
        return 0;
    while (ptr) {
        if (!validate_number(ptr))
            return 0;
        int num = atoi(ptr);
        if (num >= 0 && num <= 255) {
            ptr = strtok(NULL, ".");
            if (ptr != NULL)
                dots++;
        } else
            return 0;
    }
    if (dots != 3)
        return 0;
    return 1;
}

int validate_port(const char *port) {
    if (port == NULL)
        return 0;
    if (!validate_number(port))
        return 0;
    const int res = atoi(port);
    return res >= 1 && res < +65535;
}
