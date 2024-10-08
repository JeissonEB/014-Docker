#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include "./headers/commonHttpFunctions.h"
#include "./headers/net.h"
#include "./headers/argValidator.h"

const char *help_string = "Usage: server <puerto>\n";

void key_listener() {
    int ch = 0;
    printf("Press q to kill all threads and terminate server\n");
    // Wait for character "q" to be pressed
    while (ch != 113) {
        ch = getchar();
    }
    kill(0, SIGUSR1);
}

void signal_handler(int signal) {
    if (signal == SIGUSR1) {
        _exit(0);
    }
}

int main(const int argc, char **argv) {
    char port[6] = "";
    struct sockaddr_storage their_addr;

    signal(SIGUSR1, signal_handler);

    // Launch a fork to handle stdin and check if user wants to stop the program
    const pid_t keyboard_listener_pid = fork();
    if (keyboard_listener_pid != 0) {
        key_listener();
        return 0;
    }

    //Check the count of arguments
    if (argc < 2)
        errExit(help_string);

    // Validate program arguments
    if (!validate_port(argv[1])) errExit("Invalid port");

    // Clean variables
    memset(port, 0, 6);

    // Copy data to variables
    strncpy(port, argv[1], strlen(argv[1]));

    const int listenfd = get_listener_socket(port);
    if (listenfd < 0) {
        errExit("webServer: fatal error getting listening socket\n");
    }
    while (1) {
        char s[INET6_ADDRSTRLEN];
        socklen_t sin_size = sizeof their_addr;
        const int newfd = accept(listenfd, (struct sockaddr *) &their_addr, &sin_size);
        if (newfd == -1) {
            perror("Accept Invalid");
            continue;
        }
        inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
        handle_http_request(newfd);
    }
}
